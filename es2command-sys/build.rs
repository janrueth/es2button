use std::{env, fs, path::PathBuf};

fn main() {
    let out_dir = env::var_os("OUT_DIR").unwrap();

    let install_lib_dir = format!(
        r#""/usr/lib/{}-{}-{}""#,
        env::var("CARGO_CFG_TARGET_ARCH").unwrap(),
        env::var("CARGO_CFG_TARGET_OS").unwrap(),
        env::var("CARGO_CFG_TARGET_ENV").unwrap()
    );

    let mut builder = cc::Build::new();
    builder
        .file("cinterface/src/delegate.cpp")
        .file("cinterface/src/scanner.cpp")
        .file("cinterface/src/wrapper.cpp")
        .define("INSTALL_LIB_DIR", install_lib_dir.as_str())
        .include("cinterface/include")
        .flag("-Wno-unused-parameter")
        .flag("-Wno-unused-variable")
        .flag("-Wno-missing-field-initializers")
        .static_flag(true)
        .cpp(true)
        .std("c++11")
        .pic(true);

    #[cfg(debug_assertions)]
    builder.debug(true);

    builder.compile("es2commandwrapper");

    println!("cargo:rerun-if-changed=cinterface/src/delegate.cpp");
    println!("cargo:rerun-if-changed=cinterface/src/internal.hpp");
    println!("cargo:rerun-if-changed=cinterface/src/scanner.cpp");
    println!("cargo:rerun-if-changed=cinterface/src/wrapper.cpp");

    println!(
        "cargo:rustc-link-search=native={}",
        out_dir.to_str().unwrap()
    );
    println!("cargo:rustc-link-lib=static=es2commandwrapper");

    let builder = bindgen::Builder::default()
        .clang_args([
            "-Icinterface/include",
            "-x",
            "c++",
            "-std=c++11",
            &format!("-DINSTALL_LIB_DIR={}", install_lib_dir.as_str()),
        ])
        .use_core()
        .ctypes_prefix("::core::ffi")
        .header("cinterface/include/wrapper.hpp")
        .allowlist_file("cinterface/include/wrapper.hpp")
        .allowlist_file("cinterface/include/ES2Command/ES2CommandAPI.h")
        .blocklist_function("ESCreateScanner")
        .allowlist_file("cinterface/include/ES2Command/ESCommandProperties.h")
        .allowlist_file("cinterface/include/ES2Command/ESPropertyKeys.h")
        .allowlist_file("cinterface/include/common.hpp")
        .allowlist_file("cinterface/include/delegate.hpp")
        .allowlist_file("cinterface/include/scanner.hpp")
        .rustified_enum("ES.*")
        .emit_builtins()
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .formatter(bindgen::Formatter::Prettyplease);

    // cross compile support
    let builder = if env::var("HOST").unwrap() != env::var("TARGET").unwrap() {
        let re = regex::RegexBuilder::new(r"^ .*$")
            .multi_line(true)
            .build()
            .unwrap();
        let cc_paths = cc::Build::new()
            .get_compiler()
            .to_command()
            .args(["-E", "-Wp,-v", "-xc++", "/dev/null"])
            .output()
            .unwrap()
            .stderr;

        let include_paths: Vec<_> = re
            .find_iter(std::str::from_utf8(&cc_paths).unwrap())
            .map(|m| format!("-I{}", &m.as_str()[1..]))
            .collect();

        builder.clang_args(include_paths)
    } else {
        builder
    };

    let bindings = builder.generate().unwrap();

    // we'll derive Serialize_repr for the enums
    let mut output = b"use serde_repr::*;\n".to_vec();

    bindings
        .write(Box::new(&mut output))
        .expect("failed generating bindings");

    let re = regex::Regex::new(r"#\[derive\((.*)\)\]\npub enum").unwrap();

    let bindings = re
        .replace_all(
            std::str::from_utf8(&output[..]).unwrap(),
            "#[derive(Serialize_repr, Deserialize_repr, $1)]\npub enum",
        )
        .to_string();

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(out_dir);
    fs::write(out_path.join("bindings.rs"), bindings).expect("Couldn't write bindings!");
}
