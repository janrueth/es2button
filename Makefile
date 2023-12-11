
.PHONY: fmt
fmt:
	cargo fmt --all --check

.PHONY: lint
lint:
	cargo clippy --workspace --all-targets

.PHONY: test
test:
	cargo test --all-targets

.PHONY: build
build:
	cargo build --release -p es2button

.PHONY: deb
deb:
ifeq ($(TARGET),) 
	cargo deb -p es2button --no-build -o target/debian/
else
	cargo deb -p es2button --no-build --target $(TARGET) -o target/debian/
endif

.PHONY: build-cross
build-cross:
	cross build -p es2button --target $(TARGET) --release