use std::{
    error::Error,
    io::{self, Write},
    path::PathBuf,
    process::Command,
};

use anyhow::Context;
use es2command::{ESError, ScannerRef, UsbConnectInfo};
use log::{debug, error, info, trace};
use nix::unistd::getpid;
use signal_hook::consts::{SIGINT, SIGPIPE};

use crate::types::UsbDevice;

pub struct Listener<'a> {
    program: PathBuf,
    device: UsbDevice,
    scanner: &'a ScannerRef,
}

impl<'a> Listener<'a> {
    pub fn new(device: UsbDevice, program: PathBuf, scanner: &'a ScannerRef) -> Self {
        Self {
            program,
            device,
            scanner,
        }
    }
}

pub(crate) fn run_listener(device: UsbDevice, program: PathBuf) -> Result<(), Box<dyn Error>> {
    let scanner = es2command::Scanner::default();

    let connect_info = serde_json::to_string(&UsbConnectInfo::from(device.clone()))
        .context("failed serializing connection information to scanner")?;
    trace!("Connecting: {}", &connect_info);
    scanner
        .set_connection(&connect_info)
        .context("failed setting connection to scanner")?;

    scanner.set_delegate(Listener::new(device, program, &scanner));

    scanner.open().context("failed opening scanner")?;

    // wait until we're told to close
    let mut signals = signal_hook::iterator::Signals::new([SIGINT, SIGPIPE])
        .context("failed creating signal listener")?;

    'outer: loop {
        for signal in signals.wait() {
            match signal {
                SIGINT => {
                    info!("Got SIGINT terminating");
                    break 'outer;
                }
                SIGPIPE => {
                    info!("Got SIGPIPE, scanner is gone, terminating");
                    break 'outer;
                }
                num => {
                    info!("Got unknown signal {}, ignoring it", num);
                }
            }
        }
    }

    scanner.close().context("failed closing closing scanner")?;
    Ok(())
}

impl<'a> Listener<'a> {
    fn is_document_loaded(&self) -> Result<bool, ESError> {
        self.scanner
            .get_bool_value_for_key(es2command::ESKEY_DOCUMENT_LOADED)
    }

    fn is_card_scanning(&self) -> Result<bool, ESError> {
        match self
            .scanner
            .get_bool_value_for_key(es2command::ESKEY_CARD_SCANNING)
        {
            // Not all scanners support card scanning, in this case,
            // we get a InvalidParameter, we just report this as no card scanning
            Err(ESError::InvalidParameter) => {
                trace!("Got InvalidParameter for \"cardScanning\" lookup, assuming no card scanning available");
                Ok(false)
            }
            x => x,
        }
    }

    fn handle_button_press(&self, button: u8) -> Result<(), anyhow::Error> {
        debug!("Button pressed: {}", button);

        trace!("Checking scanner document state");
        let doc_present = self
            .is_document_loaded()
            .context("checking document status")?;
        let card_scanning = self.is_card_scanning().context("checking card scanning")?;

        trace!("Disconnecting from scanner");
        self.scanner.close().context("closing scanner")?;

        trace!("Spawning process");
        let output = Command::new(&self.program)
            .env_clear()
            .env("ES2_BUTTON_NUM", format!("{}", button))
            .env("ES2_DOC_PRESENT", b2str(doc_present))
            .env("ES2_CARD_SCANNING", b2str(card_scanning))
            .env(
                "ES2_DEV",
                format!(
                    "{}:{:03}:{:03}",
                    self.device.identifier.name,
                    self.device.identifier.bus,
                    self.device.identifier.dev
                ),
            )
            .env("ES2_DEV_VID", format!("{:03}", self.device.vid))
            .env("ES2_DEV_PID", format!("{:03}", self.device.pid))
            .output()
            .expect("program execution failed"); // do not error here as we can't open the scanner otherwise, user needs to fix their script

        info!("Script status: {}", output.status);
        info!("Script stdout:");
        io::stdout().write_all(&output.stdout).unwrap();
        info!("Script stderr:");
        io::stdout().write_all(&output.stderr).unwrap();
        info!("Resuming from script");

        trace!("Reopening connection to scanner");
        self.scanner.open().context("opening scanner")
    }
}

impl<'a> es2command::ScanDelegate for Listener<'a> {
    fn did_encounter_device_communication_error(
        &self,
        _scanner: &es2command::ScannerRef,
        error: es2command::ESError,
    ) {
        debug!("Communication error: {}", error);
        trace!("Stopping");
        //  wakeup listener
        nix::sys::signal::kill(getpid(), nix::sys::signal::SIGPIPE).unwrap();
    }

    fn did_press_button(&self, button: u8) {
        if let Err(err) = self.handle_button_press(button) {
            error!("failed handling button press: {:#}", err);
        }
    }

    fn will_begin_continous_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn did_end_continuous_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn will_cancel_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn did_cancel_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn did_complete_scanning_with_error(
        &self,
        _scanner: &es2command::ScannerRef,
        _error: es2command::ESError,
    ) {
    }

    fn did_interrupt_scanning_with_error(
        &self,
        _scanner: &es2command::ScannerRef,
        _error: es2command::ESError,
    ) {
    }

    fn will_warm_up(&self, _scanner: &es2command::ScannerRef) {}

    fn did_warm_up(&self, _scanner: &es2command::ScannerRef) {}

    fn network_did_request_start_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn network_did_request_stop_scanning(&self, _scanner: &es2command::ScannerRef) {}

    fn did_disconnect(&self, _scanner: &es2command::ScannerRef) {}

    fn network_did_receive_server_error(&self, _scanner: &es2command::ScannerRef) {}

    fn network_should_prevent_timeout(&self, _scanner: &es2command::ScannerRef) -> bool {
        false
    }

    fn network_did_timeout(&self, _scanner: &es2command::ScannerRef) {}

    fn is_reserved_by_host(&self, _scanner: &es2command::ScannerRef, _host: String) {}

    fn network_did_request_stop(&self, _scanner: &es2command::ScannerRef) {}

    fn network_did_request_push_scan_connection(&self, _scanner: &es2command::ScannerRef) {}

    fn network_did_notify_status_change(&self, _scanner: &es2command::ScannerRef) {}
}

fn b2str(b: bool) -> &'static str {
    if b {
        "Yes"
    } else {
        "No"
    }
}
