use crate::ESError;

pub(crate) fn cvt(error_code: es2command_sys::ESErrorCode) -> Result<(), ESError> {
    match ESError::from(error_code) {
        ESError::NoError => Ok(()),
        x => Err(x),
    }
}
