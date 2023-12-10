use serde::Serialize;
use thiserror::Error;

// Reexport types
pub use es2command_sys::ESConnectionType;

#[macro_export]
macro_rules! str_from_cstr {
    ($lit:expr) => {
        if let Some((_, x)) = $lit.split_last() {
            unsafe { std::str::from_utf8_unchecked(x) }
        } else {
            ""
        }
    };
}
pub const ESKEY_DOCUMENT_LOADED: &str = str_from_cstr!(es2command_sys::kESDocumentLoaded);
pub const ESKEY_CARD_SCANNING: &str = str_from_cstr!(es2command_sys::kESCardScanning);

#[derive(Error, Debug)]
pub enum ESError {
    #[error("Success")]
    NoError,
    #[error("Fatal Error")]
    FatalError,
    #[error("Invalid Parameter")]
    InvalidParameter,

    // Driver internal error
    #[error("internal error: memory error")]
    MemoryError,
    #[error("internal error: sequence error")]
    SequenceError,
    #[error("internal error: file write error")]
    FileWriteError,
    #[error("internal error: file read error")]
    FileReadError,
    #[error("internal error: scan area too large error")]
    ScanAreaTooLargeError,

    // Communication error
    #[error("communication error: data send failure")]
    DataSendFailure, // データー転送エラー
    #[error("communication error: data receive failure")]
    DataReceiveFailure, // データー受信エラー
    #[error("communication error: invalid response")]
    InvalidResponse, // 不正なレスポンス
    #[error("communication error: device open error")]
    DeviceOpenError,

    // Device error
    #[error("device error: device in use")]
    DeviceInUse,
    #[error("device error: device busy")]
    DeviceInBusy,
    #[error("device error: paper empty")]
    PaperEmpty,
    #[error("device error: paper jam")]
    PaperJam,
    #[error("device error: paper double feed")]
    PaperDoubleFeed,
    #[error("device error: cover open")]
    CoverOpen,
    #[error("device error: tray close")]
    TrayClose,
    #[error("device error: cr lock")]
    CRLock,
    #[error("device error: lamp error")]
    LampError,
    #[error("device error: lamp time")]
    LampTime,
    #[error("device error: auth failure")]
    AuthFailure,
    #[error("device error: no permission")]
    NoPermission,
    #[error("device error: low battery")]
    LowBattery,
    #[error("device error: focus error")]
    FocusError,
    #[error("device error: fatal error")]
    DeviceFatalError,
    #[error("device error: cr sheet sensor error")]
    CRSheetSensorError,
    #[error("device error: paper protect")]
    PaperProtect,
    #[error("device error: gap sensor error")]
    GAPSensorError,
    #[error("device error: paper double feed 2")]
    PaperDoubleFeed2,
    #[error("device error: pose error")]
    PoseError,
    #[error("device error: separation level error")]
    SeparationLeverError,
    #[error("device error: et sensor error")]
    ETSensorError,
    #[error("device error: adf lift error")]
    ADFLiftError,
    #[error("device error: user auth enabled")]
    UserAuthEnabled,
    #[error("device error: print stacker error")]
    PrintStackerError,
    #[error("device error: paper remove error")]
    PaperRemoveError,
    #[error("device error: skew detect error")]
    SkewDetectError,

    #[error("unknown error: {0}")]
    UnknownError(u32),
}

impl From<es2command_sys::ESErrorCode> for ESError {
    fn from(value: es2command_sys::ESErrorCode) -> Self {
        match value {
            es2command_sys::ESErrorCode::kESErrorNoError => ESError::NoError,

            es2command_sys::ESErrorCode::kESErrorFatalError => ESError::FatalError,
            es2command_sys::ESErrorCode::kESErrorInvalidParameter => ESError::InvalidParameter,

            es2command_sys::ESErrorCode::kESErrorMemoryError => ESError::MemoryError,
            es2command_sys::ESErrorCode::kESErrorSequenceError => ESError::SequenceError,
            es2command_sys::ESErrorCode::kESErrorFileWriteError => ESError::FileWriteError,
            es2command_sys::ESErrorCode::kESErrorFileReadError => ESError::FileReadError,
            es2command_sys::ESErrorCode::kESErrorScanAreaTooLargeError => {
                ESError::ScanAreaTooLargeError
            }

            es2command_sys::ESErrorCode::kESErrorDataSendFailure => ESError::DataSendFailure,
            es2command_sys::ESErrorCode::kESErrorDataReceiveFailure => ESError::DataReceiveFailure,
            es2command_sys::ESErrorCode::kESErrorInvalidResponse => ESError::InvalidResponse,
            es2command_sys::ESErrorCode::kESErrorDeviceOpenError => ESError::DeviceOpenError,

            es2command_sys::ESErrorCode::kESErrorDeviceInUse => ESError::DeviceInUse,
            es2command_sys::ESErrorCode::kESErrorDeviceInBusy => ESError::DeviceInBusy,
            es2command_sys::ESErrorCode::kESErrorPaperEmpty => ESError::PaperEmpty,
            es2command_sys::ESErrorCode::kESErrorPaperJam => ESError::PaperJam,
            es2command_sys::ESErrorCode::kESErrorPaperDoubleFeed => ESError::PaperDoubleFeed,
            es2command_sys::ESErrorCode::kESErrorCoverOpen => ESError::CoverOpen,
            es2command_sys::ESErrorCode::kESErrorTrayClose => ESError::TrayClose,
            es2command_sys::ESErrorCode::kESErrorCRLock => ESError::CRLock,
            es2command_sys::ESErrorCode::kESErrorLampError => ESError::LampError,
            es2command_sys::ESErrorCode::kESErrorLampTime => ESError::LampTime,
            es2command_sys::ESErrorCode::kESErrorAuthFailure => ESError::AuthFailure,
            es2command_sys::ESErrorCode::kESErrorNoPermission => ESError::NoPermission,
            es2command_sys::ESErrorCode::kESErrorLowBattery => ESError::LowBattery,
            es2command_sys::ESErrorCode::kESErrorFocusError => ESError::FocusError,
            es2command_sys::ESErrorCode::kESErrorDeviceFatalError => ESError::DeviceFatalError,
            es2command_sys::ESErrorCode::kESErrorCRSheetSensorError => ESError::CRSheetSensorError,
            es2command_sys::ESErrorCode::kESErrorPaperProtect => ESError::PaperProtect,
            es2command_sys::ESErrorCode::kESErrorGAPSensorError => ESError::GAPSensorError,
            es2command_sys::ESErrorCode::kESErrorPaperDoubleFeed2 => ESError::PaperDoubleFeed2,
            es2command_sys::ESErrorCode::kESErrorPoseError => ESError::PoseError,
            es2command_sys::ESErrorCode::kESErrorSeparationLeverError => {
                ESError::SeparationLeverError
            }
            es2command_sys::ESErrorCode::kESErrorETSensorError => ESError::ETSensorError,
            es2command_sys::ESErrorCode::kESErrorADFLiftError => ESError::ADFLiftError,
            es2command_sys::ESErrorCode::kESErrorUserAuthEnabled => ESError::UserAuthEnabled,
            es2command_sys::ESErrorCode::kESErrorPrintStackerError => ESError::PrintStackerError,
            es2command_sys::ESErrorCode::kESErrorPaperRemoveError => ESError::PaperRemoveError,
            es2command_sys::ESErrorCode::kESErrorSkewDetectError => ESError::SkewDetectError,
            //v => ESError::UnknownError(v as u32),
        }
    }
}

#[repr(u8)]
pub enum ESJobMode {
    None = es2command_sys::kESJobModeNone as u8,
    Standard = es2command_sys::kESJobModeStandard as u8,
    Continue = es2command_sys::kESJobModeContinue as u8,
    AFM = es2command_sys::kESJobModeAFM as u8,
    AFMC = es2command_sys::kESJobModeAFMC as u8,
}

#[derive(Debug, Serialize)]
pub enum TypeInt<T> {
    #[serde(rename = "int")]
    Int(T),
}

#[derive(Debug, Serialize)]
pub struct ConnectionSettings {
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_TYPE`]
    #[serde(rename = "ConnectType")]
    pub connect_type: TypeInt<ESConnectionType>,
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_VID`]
    #[serde(rename = "VID")]
    pub vid: TypeInt<u16>,
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_PID`]
    #[serde(rename = "PID")]
    pub pid: TypeInt<u16>,
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_BUS_NUMBER`]
    #[serde(rename = "BUS_NUMBER")]
    pub bus_number: TypeInt<u8>,
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_DEVICE_NUMBER`]
    #[serde(rename = "DEVICE_NUMBER")]
    pub device_number: TypeInt<u8>,
}

#[derive(Debug, Serialize)]
pub struct UsbConnectInfo {
    /// Encoded as [`es2command_sys::ES_CNCT_KEY_ROOT`]
    #[serde(rename = "ConnectionSetting")]
    pub connection_setting: Vec<ConnectionSettings>,
}
