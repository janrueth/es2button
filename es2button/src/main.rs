mod list;
mod listener;
mod types;
use std::path::PathBuf;

use clap::Parser;
use types::UsbIdentifier;

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// The scanner device
    #[arg(short, long)]
    device: Option<String>,

    /// List scanner devices
    #[arg(short, long)]
    list: bool,

    #[clap(index = 1)]
    pub program: Option<PathBuf>,
}

fn main() {
    let args = Args::parse();

    let mut available_devices = list::epson_scanners();

    if args.list {
        for device in available_devices {
            println!(
                "{}:{:03}:{:03}",
                &device.identifier.name, device.identifier.bus, device.identifier.dev
            );
        }
        return;
    }

    if available_devices.is_empty() {
        println!("No devices found");
        return;
    }

    let target_device = if let Some(device) = args.device {
        let identifier = UsbIdentifier::try_from(device.as_str()).expect("invalid device");
        available_devices
            .into_iter()
            .find(|x| x.identifier == identifier)
            .expect("device not found")
    } else {
        available_devices.reverse();
        available_devices.pop().unwrap()
    };

    listener::run_listener(
        target_device,
        args.program
            .unwrap_or(PathBuf::from("/etc/es2button/entrypoint")),
    )
}
