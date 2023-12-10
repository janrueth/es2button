use std::{
    ffi::{CStr, CString},
    mem::MaybeUninit,
    path::{Path, PathBuf},
    str::FromStr,
};

use crate::{helper::cvt, Delegate, ESError, ESJobMode, NonDelegate, ScanDelegate};
use es2command_sys::ESCommandType;
use foreign_types::{foreign_type, ForeignType, ForeignTypeRef};
use libloading::Symbol;

foreign_type! {

    pub unsafe type Scanner: Sync + Send
    {
        type CType = es2command_sys::scanner_t;
        fn drop = scanner_free;
    }
}

unsafe fn scanner_free(scanner: *mut es2command_sys::scanner_t) {
    let delegate = es2command_sys::scanner_destroy_instance(scanner);
    // if the scanner had a delegate
    // we now own it, so we need to release it as well
    if !delegate.is_null() {
        let _ = Delegate::<NonDelegate>::from_ptr(delegate);
    }
    es2command_sys::scanner_free(scanner)
}

impl Default for Scanner {
    fn default() -> Self {
        let install_dir =
            unsafe { CStr::from_ptr(es2command_sys::DEFAULT_INSTALL_LIB_DIR[..].as_ptr() as _) };
        let library_path = PathBuf::from_str(install_dir.to_str().unwrap())
            .unwrap()
            .join("libes2command.so");
        Self::new(&library_path, ESCommandType::kESCommandTypeESCI2).unwrap()
    }
}

impl Scanner {
    pub fn new(library_path: &Path, cmd_type: ESCommandType) -> Result<Self, ESError> {
        let library = unsafe { libloading::Library::new(library_path) }.unwrap();
        let es_create_scanner: Symbol<es2command_sys::PFN_CREATE_SCANNER> =
            unsafe { library.get(es2command_sys::DEFAULT_ES_CREATE_SCANNER_SYMBOL_NAME) }.unwrap();

        Ok(unsafe {
            let mut scanner: MaybeUninit<*mut es2command_sys::scanner_t> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_create(
                *es_create_scanner,
                cmd_type,
                scanner.as_mut_ptr(),
            ))?;

            Self::from_ptr(scanner.assume_init())
        })
    }
}

impl ScannerRef {
    /// Set the delegate receiving scanner events
    pub fn set_delegate<T: ScanDelegate>(&self, delegate: T) {
        let delegate = Delegate::new(delegate);
        // es2command_sys owns the delegate memory from here
        unsafe { es2command_sys::scanner_set_delegate(self.as_ptr(), delegate.into_ptr()) }
    }

    /// Configure the connection to the scanner
    pub fn set_connection(&self, json: &str) -> Result<(), ESError> {
        let json = CString::new(json).unwrap();
        unsafe {
            cvt(es2command_sys::scanner_set_connection(
                self.as_ptr(),
                json.as_ptr(),
            ))
        }
    }

    /// Open the scanner
    pub fn open(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_open(self.as_ptr()) })
    }

    /// Close the scanner
    pub fn close(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_close(self.as_ptr()) })
    }

    /// Check if the scanner is opened
    pub fn is_opened(&self) -> bool {
        unsafe { es2command_sys::scanner_is_opened(self.as_ptr()) }
    }

    /// Start a scan
    pub fn scan(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_scan(self.as_ptr()) })
    }

    /// Scan in background
    pub fn scan_in_background(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_scan_in_background(self.as_ptr()) })
    }

    /// Cancel the current scan
    pub fn cancel(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_cancel(self.as_ptr()) })
    }

    /// Abort the current scan
    pub fn abort(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_abort(self.as_ptr()) })
    }

    /// Is the scanner currently scanning?
    pub fn is_scanning(&self) -> bool {
        unsafe { es2command_sys::scanner_is_scanning(self.as_ptr()) }
    }

    /// Perform cleaning
    pub fn do_cleaning(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_do_cleaning(self.as_ptr()) })
    }

    /// Perform calibration
    pub fn do_calibration(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_do_calibration(self.as_ptr()) })
    }

    /// Check if the scanner was interrupted
    pub fn is_interrupted(&self) -> bool {
        unsafe { es2command_sys::scanner_is_interrupted(self.as_ptr()) }
    }

    /// Check if the auto feeding mode (AFM) is enabled
    pub fn is_afm_enabled(&self) -> bool {
        unsafe { es2command_sys::scanner_is_afm_enabled(self.as_ptr()) }
    }

    /// Schedule the auto feeding mode (AFM) timeout
    pub fn schedule_auto_feeding_mode_timeout(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_schedule_auto_feeding_mode_timeout(self.as_ptr()) })
    }

    /// Start a job in the supplied mode
    pub fn start_job_in_mode(&self, mode: ESJobMode) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_start_job_in_mode(self.as_ptr(), mode as u8) })
    }

    /// Stop job in mode
    pub fn stop_job_in_mode(&self, mode: ESJobMode) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_stop_job_in_mode(self.as_ptr(), mode as u8) })
    }

    /// Perform auto focus
    pub fn do_auto_focus(&self) -> Result<f32, ESError> {
        let mut focus = 0.0;
        cvt(unsafe { es2command_sys::scanner_do_auto_focus(self.as_ptr(), &mut focus) })?;
        Ok(focus)
    }

    pub fn set_panel_to_push_scan_ready(&self, push_scan_read: bool) -> Result<(), ESError> {
        cvt(unsafe {
            es2command_sys::scanner_set_panel_to_push_scan_ready(self.as_ptr(), push_scan_read)
        })
    }

    pub fn is_scannable_device_config(&self) -> bool {
        unsafe { es2command_sys::scanner_is_scannable_device_config(self.as_ptr()) }
    }

    pub fn unlock_administrator_lock(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_unlock_administrator_lock(self.as_ptr()) })
    }

    pub fn lock_administrator_lock(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_lock_administrator_lock(self.as_ptr()) })
    }

    pub fn reset(&self) -> Result<(), ESError> {
        cvt(unsafe { es2command_sys::scanner_reset(self.as_ptr()) })
    }

    pub fn get_all_keys(&self) -> Result<String, ESError> {
        let cstr = unsafe {
            let mut keys: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_all_keys(
                self.as_ptr(),
                keys.as_mut_ptr(),
            ))?;
            CStr::from_ptr(keys.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!("Got all value from scanner, values: {}", x);
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }

    pub fn get_default_value_for_key(&self, key: &str) -> Result<String, ESError> {
        let cstr_key = CString::new(key).unwrap();
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_default_value_for_key(
                self.as_ptr(),
                cstr_key.as_ptr(),
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!(
                    "Got default value from scanner, for key: {}, value: {}",
                    key,
                    x
                );
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }

    pub fn get_value_for_key(&self, key: &str) -> Result<String, ESError> {
        let cstr_key = CString::new(key).unwrap();
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_value_for_key(
                self.as_ptr(),
                cstr_key.as_ptr() as _,
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!("Got value from scanner, for key: {}, value: {}", key, x);
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }

        out
    }

    pub fn get_bool_value_for_key(&self, key: &str) -> Result<bool, ESError> {
        let value = self.get_value_for_key(key)?;

        // this returns {"$key": {"boolean": false|true}}
        let value: serde_json::Value =
            serde_json::from_str(&value).map_err(|_| ESError::InvalidResponse)?;

        value
            .as_object()
            .and_then(|f| f.get(key))
            .and_then(|f| f.as_object())
            .and_then(|f| f.get("boolean"))
            .and_then(|f| f.as_bool())
            .ok_or(ESError::InvalidResponse)
    }

    pub fn set_value_for_key(&mut self, key: &str, value: &str) -> Result<(), ESError> {
        let key = CString::new(key).unwrap();
        let value = CString::new(value).unwrap();
        unsafe {
            cvt(es2command_sys::scanner_set_value_for_key(
                self.as_ptr(),
                key.as_ptr(),
                value.as_ptr(),
            ))
        }
    }
    pub fn set_values_with_json(&mut self, json: &str) -> Result<(), ESError> {
        let json = CString::new(json).unwrap();

        unsafe {
            cvt(es2command_sys::scanner_set_values_with_JSON(
                self.as_ptr(),
                json.as_ptr(),
            ))
        }
    }

    pub fn get_all_values_for_key(&self, key: &str) -> Result<String, ESError> {
        let cstr_key = CString::new(key).unwrap();
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_all_values_for_key(
                self.as_ptr(),
                cstr_key.as_ptr() as _,
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!(
                    "Got all values from scanner, for key: {}, values: {}",
                    key,
                    x
                );
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }

    pub fn get_all_values(&self) -> Result<String, ESError> {
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_all_values(
                self.as_ptr(),
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!("Got all values from scanner, values: {}", x);
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }

    pub fn get_available_values_for_key(&self, key: &str) -> Result<String, ESError> {
        let cstr_key = CString::new(key).unwrap();
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_available_values_for_key(
                self.as_ptr(),
                cstr_key.as_ptr() as _,
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!(
                    "Got available values from scanner, for key: {}, values: {}",
                    key,
                    x
                );
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }

    pub fn get_all_available_values(&self) -> Result<String, ESError> {
        let cstr = unsafe {
            let mut value: MaybeUninit<*mut core::ffi::c_char> = MaybeUninit::uninit();
            cvt(es2command_sys::scanner_get_all_available_values(
                self.as_ptr(),
                value.as_mut_ptr(),
            ))?;
            CStr::from_ptr(value.assume_init())
        };
        let out = cstr
            .to_str()
            .map_err(|_| ESError::InvalidResponse)
            .map(|x| {
                log::trace!("Got all available values from scanner, values: {}", x);
                x.to_owned()
            });
        unsafe {
            libc::free(cstr.as_ptr() as _);
        }
        out
    }
}

impl PartialEq for ScannerRef {
    fn eq(&self, other: &Self) -> bool {
        unsafe { es2command_sys::scanner_eq(self.as_ptr(), other.as_ptr()) }
    }
}
