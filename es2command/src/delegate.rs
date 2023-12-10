use std::{ffi::CStr, marker::PhantomData, ptr::NonNull};

use crate::{ESError, ScannerRef};
use es2command_sys::ESErrorCode;
use foreign_types::{foreign_type, ForeignTypeRef};
use libc::c_void;

pub trait ScanDelegate {
    fn did_encounter_device_communication_error(&self, scanner: &ScannerRef, error: ESError);
    fn did_press_button(&self, button: u8);
    fn will_begin_continous_scanning(&self, scanner: &ScannerRef);
    fn did_end_continuous_scanning(&self, scanner: &ScannerRef);
    fn will_cancel_scanning(&self, scanner: &ScannerRef);
    fn did_cancel_scanning(&self, scanner: &ScannerRef);
    fn did_complete_scanning_with_error(&self, scanner: &ScannerRef, error: ESError);
    fn did_interrupt_scanning_with_error(&self, scanner: &ScannerRef, error: ESError);
    fn will_warm_up(&self, scanner: &ScannerRef);
    fn did_warm_up(&self, scanner: &ScannerRef);
    fn network_did_request_start_scanning(&self, scanner: &ScannerRef);
    fn network_did_request_stop_scanning(&self, scanner: &ScannerRef);
    fn did_disconnect(&self, scanner: &ScannerRef);
    fn network_did_receive_server_error(&self, scanner: &ScannerRef);
    fn network_should_prevent_timeout(&self, scanner: &ScannerRef) -> bool;
    fn network_did_timeout(&self, scanner: &ScannerRef);
    fn is_reserved_by_host(&self, scanner: &ScannerRef, host: String);
    fn network_did_request_stop(&self, scanner: &ScannerRef);
    fn network_did_request_push_scan_connection(&self, scanner: &ScannerRef);
    fn network_did_notify_status_change(&self, scanner: &ScannerRef);
}

foreign_type! {
    pub unsafe type Delegate<T: ScanDelegate>: Sync + Send
    {
        type CType = es2command_sys::delegate_t;
        type PhantomData = T;
        fn drop = es2command_sys::delegate_free;
    }
}

impl<T: ScanDelegate> Delegate<T> {
    pub fn new(delegate: T) -> Self {
        let delegate = Box::new(delegate);
        Self(
            NonNull::new(unsafe {
                es2command_sys::delegate_new(
                    Box::into_raw(delegate) as _,
                    Some(Self::did_encounter_device_communication_error),
                    Some(Self::did_press_button),
                    Some(Self::will_begin_continous_scanning),
                    Some(Self::did_end_continuous_scanning),
                    Some(Self::will_cancel_scanning),
                    Some(Self::did_cancel_scanning),
                    Some(Self::did_complete_scanning_with_error),
                    Some(Self::did_interrupt_scanning_with_error),
                    Some(Self::will_warm_up),
                    Some(Self::did_warm_up),
                    Some(Self::network_did_request_start_scanning),
                    Some(Self::network_did_request_stop_scanning),
                    Some(Self::did_disconnect),
                    Some(Self::network_did_receive_server_error),
                    Some(Self::network_should_prevent_timeout),
                    Some(Self::network_did_timeout),
                    Some(Self::is_reserved_by_host),
                    Some(Self::network_did_request_stop),
                    Some(Self::network_did_request_push_scan_connection),
                    Some(Self::network_did_notify_status_change),
                )
            })
            .unwrap(),
            PhantomData,
        )
    }

    unsafe fn delegate_from_target(target: &*mut c_void) -> &T {
        &*(*target as *mut T)
    }

    extern "C" fn did_encounter_device_communication_error(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
        error: ESErrorCode,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };

        target.did_encounter_device_communication_error(scanner, ESError::from(error));
    }

    extern "C" fn did_press_button(target: *mut c_void, button: u8) {
        let target = unsafe { Self::delegate_from_target(&target) };
        target.did_press_button(button)
    }

    extern "C" fn will_begin_continous_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.will_begin_continous_scanning(scanner)
    }
    extern "C" fn did_end_continuous_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_end_continuous_scanning(scanner)
    }

    extern "C" fn will_cancel_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.will_cancel_scanning(scanner)
    }

    extern "C" fn did_cancel_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_cancel_scanning(scanner)
    }

    extern "C" fn did_complete_scanning_with_error(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
        error: ESErrorCode,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_complete_scanning_with_error(scanner, ESError::from(error))
    }

    extern "C" fn did_interrupt_scanning_with_error(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
        error: ESErrorCode,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_interrupt_scanning_with_error(scanner, ESError::from(error))
    }
    extern "C" fn will_warm_up(target: *mut c_void, scanner: *mut es2command_sys::scanner_t) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.will_warm_up(scanner)
    }
    extern "C" fn did_warm_up(target: *mut c_void, scanner: *mut es2command_sys::scanner_t) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_warm_up(scanner)
    }
    extern "C" fn network_did_request_start_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_request_start_scanning(scanner)
    }

    extern "C" fn network_did_request_stop_scanning(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_request_stop_scanning(scanner)
    }

    extern "C" fn did_disconnect(target: *mut c_void, scanner: *mut es2command_sys::scanner_t) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.did_disconnect(scanner)
    }

    extern "C" fn network_did_receive_server_error(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_receive_server_error(scanner)
    }

    extern "C" fn network_should_prevent_timeout(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) -> bool {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };

        target.network_should_prevent_timeout(scanner)
    }

    extern "C" fn network_did_timeout(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_timeout(scanner)
    }

    extern "C" fn is_reserved_by_host(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
        host: *const core::ffi::c_char,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        let host = unsafe { CStr::from_ptr(host) }.to_str().unwrap().to_owned();
        target.is_reserved_by_host(scanner, host)
    }

    extern "C" fn network_did_request_stop(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_request_stop(scanner)
    }

    extern "C" fn network_did_request_push_scan_connection(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_request_push_scan_connection(scanner)
    }

    extern "C" fn network_did_notify_status_change(
        target: *mut c_void,
        scanner: *mut es2command_sys::scanner_t,
    ) {
        let (target, scanner) = unsafe {
            (
                Self::delegate_from_target(&target),
                ScannerRef::from_ptr(scanner),
            )
        };
        target.network_did_notify_status_change(scanner)
    }
}

pub(crate) struct NonDelegate();

impl ScanDelegate for NonDelegate {
    fn did_encounter_device_communication_error(&self, _scanner: &ScannerRef, _error: ESError) {}

    fn did_press_button(&self, _button: u8) {}

    fn will_begin_continous_scanning(&self, _scanner: &ScannerRef) {}

    fn did_end_continuous_scanning(&self, _scanner: &ScannerRef) {}

    fn will_cancel_scanning(&self, _scanner: &ScannerRef) {}

    fn did_cancel_scanning(&self, _scanner: &ScannerRef) {}

    fn did_complete_scanning_with_error(&self, _scanner: &ScannerRef, _error: ESError) {}

    fn did_interrupt_scanning_with_error(&self, _scanner: &ScannerRef, _rror: ESError) {}

    fn will_warm_up(&self, _scanner: &ScannerRef) {}

    fn did_warm_up(&self, _scanner: &ScannerRef) {}

    fn network_did_request_start_scanning(&self, _scanner: &ScannerRef) {}

    fn network_did_request_stop_scanning(&self, _scanner: &ScannerRef) {}

    fn did_disconnect(&self, _scanner: &ScannerRef) {}

    fn network_did_receive_server_error(&self, _scanner: &ScannerRef) {}

    fn network_should_prevent_timeout(&self, _scanner: &ScannerRef) -> bool {
        false
    }

    fn network_did_timeout(&self, _scanner: &ScannerRef) {}

    fn is_reserved_by_host(&self, _scanner: &ScannerRef, _host: String) {}

    fn network_did_request_stop(&self, _scanner: &ScannerRef) {}

    fn network_did_request_push_scan_connection(&self, _scanner: &ScannerRef) {}

    fn network_did_notify_status_change(&self, _scanner: &ScannerRef) {}
}
