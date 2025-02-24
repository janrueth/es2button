use std::time::Duration;

use rusb::UsbContext;

use crate::types::{self, UsbDevice, UsbIdentifier};

const EPSON_USB_VID: u16 = 0x04b8;

pub(crate) fn epson_scanners() -> Vec<UsbDevice> {
    let mut devices = Vec::<types::UsbDevice>::new();

    let ctx = rusb::Context::new().unwrap();
    for device in ctx.devices().unwrap().iter() {
        let descriptor = device.device_descriptor().unwrap();

        if descriptor.vendor_id() != EPSON_USB_VID {
            continue;
        }
        let handle = device.open().unwrap();
        handle.reset().unwrap();

        let langs = handle.read_languages(Duration::from_secs(1)).unwrap();
        if langs.is_empty() {
            continue;
        }

        let name = handle
            .read_product_string(langs[0], &descriptor, Duration::from_secs(1))
            .unwrap();
        let vid = descriptor.vendor_id();
        let pid = descriptor.product_id();
        let bus = device.bus_number();
        let dev = device.address();

        devices.push(UsbDevice {
            identifier: UsbIdentifier { name, bus, dev },
            vid,
            pid,
        })
    }
    devices
}
