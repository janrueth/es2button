mod list;
mod listener;
mod types;
use std::{error::Error, path::PathBuf};

use anyhow::{anyhow, Context};
use clap::Parser;
use types::UsbIdentifier;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// The scanner device
    #[arg(short, long)]
    device: Option<String>,

    /// List scanner devices
    #[arg(short, long)]
    list: bool,

    /// Which program to execute, default: etc/es2button/entrypoint
    #[clap(index = 1)]
    pub program: Option<PathBuf>,
}

fn main() -> Result<(), Box<dyn Error>> {
    env_logger::init();

    let args = Args::parse();

    let mut available_devices = list::epson_scanners();

    if args.list {
        for device in available_devices {
            println!(
                "{}:{:03}:{:03}",
                &device.identifier.name, device.identifier.bus, device.identifier.dev
            );
        }
        return Ok(());
    }

    if available_devices.is_empty() {
        return Err(anyhow!("No epson scanners found").into());
    }

    let target_device = if let Some(device) = args.device {
        let identifier = UsbIdentifier::try_from(device.as_str()).context("invalid device")?;
        available_devices
            .into_iter()
            .find(|x| x.identifier == identifier)
            .context("device not found")?
    } else {
        // no device given, take the first one
        available_devices.reverse();
        available_devices.pop().context("no device found")?
    };

    listener::run_listener(
        target_device,
        args.program.unwrap_or(
            std::env::current_exe()
                .context("failed getting location of es2button")?
                .join("../../etc/es2button/entrypoint"), // support different install prefix than `/`
        ),
    )
}
