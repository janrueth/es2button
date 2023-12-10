#include "delegate.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "ES2Command/ESCommandProperties.h"
#include "common.hpp"
#include "internal.hpp"

void ScannerDelegate::SetCtx(void* target) { this->_target = target; };

void ScannerDelegate::ScannerDidEncounterDeviceCommunicationError(
    IESScanner* pScanner, ESErrorCode err) {
  if (this->_did_encounter_device_communication_error_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_encounter_device_communication_error_cb(this->_target, &scanner,
                                                       err);
  }
};

void ScannerDelegate::ScannerDidPressButton(UInt8 un8ButtonNumber) {
  printf("Button %d pressed in wrapper, dispatching to %p\n", un8ButtonNumber,
         this->_did_press_button_cb);
  if (this->_did_press_button_cb != NULL) {
    this->_did_press_button_cb(this->_target, un8ButtonNumber);
  }
};

void ScannerDelegate::ScannerWillBeginContinuousScanning(IESScanner* pScanner) {
  if (this->_will_begin_continuous_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_will_begin_continuous_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidEndContinuousScanning(IESScanner* pScanner) {
  if (this->_did_end_continuous_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_end_continuous_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerWillScanToScannedImage(IESScanner* pScanner,
                                                    IESScannedImage* pESImage){

};

void ScannerDelegate::ScannerDidScanToScannedImage(IESScanner* pScanner,
                                                   IESScannedImage* pESImage){};

void ScannerDelegate::ScannerWillCancelScanning(IESScanner* pScanner) {
  if (this->_will_cancel_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_will_cancel_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidCancelScanning(IESScanner* pScanner) {
  if (this->_did_cancel_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_cancel_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidCompleteScanningWithError(IESScanner* pScanner,
                                                          ESErrorCode err) {
  if (this->_did_complete_scanning_with_error_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_complete_scanning_with_error_cb(this->_target, &scanner, err);
  }
};

void ScannerDelegate::ScannerDidInterruptScanningWithError(IESScanner* pScanner,
                                                           ESErrorCode err) {
  if (this->_did_interrupt_scanning_with_error_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_interrupt_scanning_with_error_cb(this->_target, &scanner, err);
  }
};

void ScannerDelegate::ScannerWillWarmUp(IESScanner* pScanner) {
  if (this->_will_warm_up_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_will_warm_up_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidWarmUp(IESScanner* pScanner) {
  if (this->_did_warm_up_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_warm_up_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::NetworkScannerDidRequestStartScanning(
    IESScanner* pScanner) {
  if (this->_network_did_request_start_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_network_did_request_start_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::NetworkScannerDidRequestStopScanning(
    IESScanner* pScanner) {
  if (this->_network_did_request_stop_scanning_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_network_did_request_stop_scanning_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidDisconnect(IESScanner* pScanner) {
  if (this->_did_disconnect_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_disconnect_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::NetworkScannerDidReceiveServerError(
    IESScanner* pScanner) {
  if (this->_network_did_receive_server_error_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_network_did_receive_server_error_cb(this->_target, &scanner);
  }
};

BOOL ScannerDelegate::NetworkScannerShouldPreventTimeout(IESScanner* pScanner) {
  if (this->_network_should_prevent_timeout_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    return this->_network_should_prevent_timeout_cb(this->_target, &scanner);
  }
  return false;
};

void ScannerDelegate::NetworkScannerDidTimeout(IESScanner* pScanner) {
  if (this->_network_did_timeout_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_network_did_timeout_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerIsReservedByHost(IESScanner* pScanner,
                                              const ES_CHAR* pszAddress) {
  if (this->_is_reserved_by_host_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_is_reserved_by_host_cb(this->_target, &scanner, pszAddress);
  }
};

void ScannerDelegate::ScannerDidRequestStop(IESScanner* pScanner) {
  if (this->_did_request_stop_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_request_stop_cb(this->_target, &scanner);
  }
};

void ScannerDelegate::ScannerDidRequestPushScanConnection(
    IESScanner* pScanner) {
  if (this->_did_request_push_scan_connection_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_request_push_scan_connection_cb(this->_target, &scanner);
  }
};
void ScannerDelegate::ScannerDidNotifyStatusChange(IESScanner* pScanner) {
  if (this->_did_notify_status_change_cb != NULL) {
    scanner_t scanner;
    scanner.obj = pScanner;
    this->_did_notify_status_change_cb(this->_target, &scanner);
  }
};

#ifdef __cplusplus
extern "C" {
#endif

delegate_t* delegate_new(
    void* ctx,
    delegate_cb_with_error_code did_encounter_device_communication_error_cb,
    delegate_cb_with_button did_press_button_cb,
    delegate_cb will_begin_continous_scanning_cb,
    delegate_cb did_end_continuous_scanning_cb,
    delegate_cb will_cancel_scanning_cb, delegate_cb did_cancel_scanning_cb,
    delegate_cb_with_error_code did_complete_scanning_with_error_cb,
    delegate_cb_with_error_code did_interrupt_scanning_with_error_cb,
    delegate_cb will_warm_up_cb, delegate_cb did_warm_up_cb,
    delegate_cb network_did_request_start_scanning_cb,
    delegate_cb network_did_request_stop_scanning_cb,
    delegate_cb did_disconnect_cb,
    delegate_cb network_did_receive_server_error_cb,
    delegate_cb_ret_bool network_should_prevent_timeout_cb,
    delegate_cb network_did_timeout_cb,
    delegate_cb_with_cstr is_reserved_by_host_cb,
    delegate_cb did_request_stop_cb,
    delegate_cb did_request_push_scan_connection_cb,
    delegate_cb did_notify_status_change_cb) {
  delegate_t* obj = (delegate_t*)malloc(sizeof(delegate_t));
  obj->ctx = ctx;
  obj->obj = new ScannerDelegate();
  obj->obj->Initialize(
      did_encounter_device_communication_error_cb, did_press_button_cb,
      will_begin_continous_scanning_cb, did_end_continuous_scanning_cb,
      will_cancel_scanning_cb, did_cancel_scanning_cb,
      did_complete_scanning_with_error_cb, did_interrupt_scanning_with_error_cb,
      will_warm_up_cb, did_warm_up_cb, network_did_request_start_scanning_cb,
      network_did_request_stop_scanning_cb, did_disconnect_cb,
      network_did_receive_server_error_cb, network_should_prevent_timeout_cb,
      network_did_timeout_cb, is_reserved_by_host_cb, did_request_stop_cb,
      did_request_push_scan_connection_cb, did_notify_status_change_cb);

  obj->obj->SetCtx(ctx);

  return obj;
}

void delegate_free(delegate_t* obj) {
  delete obj->obj;
  free(obj);
}

#ifdef __cplusplus
}
#endif
