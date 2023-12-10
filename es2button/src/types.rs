use std::num::ParseIntError;

use es2command::{ConnectionSettings, ESConnectionType, TypeInt, UsbConnectInfo};
use thiserror::Error;

#[derive(Debug, PartialEq, Clone)]
pub struct UsbDevice {
    pub identifier: UsbIdentifier,
    pub vid: u16,
    pub pid: u16,
}

impl From<UsbDevice> for UsbConnectInfo {
    fn from(value: UsbDevice) -> Self {
        Self {
            connection_setting: vec![ConnectionSettings {
                connect_type: TypeInt::Int(ESConnectionType::kESConnectionLocal),
                vid: TypeInt::Int(value.vid),
                pid: TypeInt::Int(value.pid),
                bus_number: TypeInt::Int(value.identifier.bus),
                device_number: TypeInt::Int(value.identifier.dev),
            }],
        }
    }
}

#[derive(Debug, PartialEq, Clone)]
pub struct UsbIdentifier {
    pub name: String,
    pub bus: u8,
    pub dev: u8,
}

#[derive(Debug, Error)]
pub enum ParsingError {
    #[error("invalid device identifier, need dev_name:bus:dev got: '{0}'")]
    Identifier(String),
    #[error("invalid bus, expected integer: '{0}'")]
    Bus(ParseIntError),
    #[error("invalid dev, expected integer: '{0}'")]
    Dev(ParseIntError),
}

impl TryFrom<&str> for UsbIdentifier {
    type Error = ParsingError;

    fn try_from(value: &str) -> Result<Self, Self::Error> {
        let (name, rest) = value
            .split_once(':')
            .ok_or(ParsingError::Identifier(value.into()))?;
        let (bus, dev) = rest
            .split_once(':')
            .ok_or(ParsingError::Identifier(value.into()))?;

        let bus = bus.parse().map_err(ParsingError::Bus)?;
        let dev = dev.parse().map_err(ParsingError::Dev)?;

        Ok(Self {
            name: name.to_owned(),
            bus,
            dev,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::UsbIdentifier;

    #[test]
    fn test_try_from() {
        assert!(UsbIdentifier::try_from("DS-310:1:9").is_ok());
        assert!(UsbIdentifier::try_from("DS 310:1:9").is_ok());
        assert!(UsbIdentifier::try_from("DS-310:a:9").is_err());
        assert!(UsbIdentifier::try_from("DS-310:1:b").is_err());
    }
}
