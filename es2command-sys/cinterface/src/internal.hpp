#pragma once

#include "ES2Command/IESScanner.h"
#include "delegate.hpp"

struct scanner {
  IESScanner* obj;
  delegate_t* owned_delegate;
};

class ScannerDelegate final : public IESScannerDelegate {
 private:
  void* _target;
  delegate_cb_with_error_code _did_encounter_device_communication_error_cb;
  delegate_cb_with_button _did_press_button_cb;
  delegate_cb _will_begin_continuous_scanning_cb;
  delegate_cb _did_end_continuous_scanning_cb;
  // delegate_cb_with_image will_scan_to_scanned_image(...)
  // delegate_cb_with_image did_scan_to_scanned_image(...)
  delegate_cb _will_cancel_scanning_cb;
  delegate_cb _did_cancel_scanning_cb;
  delegate_cb_with_error_code _did_complete_scanning_with_error_cb;
  delegate_cb_with_error_code _did_interrupt_scanning_with_error_cb;
  delegate_cb _will_warm_up_cb;
  delegate_cb _did_warm_up_cb;
  delegate_cb _network_did_request_start_scanning_cb;
  delegate_cb _network_did_request_stop_scanning_cb;
  delegate_cb _did_disconnect_cb;
  delegate_cb _network_did_receive_server_error_cb;
  delegate_cb_ret_bool _network_should_prevent_timeout_cb;
  delegate_cb _network_did_timeout_cb;
  delegate_cb_with_cstr _is_reserved_by_host_cb;
  delegate_cb _did_request_stop_cb;
  delegate_cb _did_request_push_scan_connection_cb;
  delegate_cb _did_notify_status_change_cb;

 public:
  //~ScannerDelegate() {}
  ScannerDelegate() {}
  void Initialize(
      delegate_cb_with_error_code did_encounter_device_communication_error_cb,
      delegate_cb_with_button did_press_button_cb,
      delegate_cb will_begin_continuous_scanning_cb,
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
    this->_did_encounter_device_communication_error_cb =
        did_encounter_device_communication_error_cb;
    this->_did_press_button_cb = did_press_button_cb;
    this->_will_begin_continuous_scanning_cb =
        will_begin_continuous_scanning_cb;
    this->_did_end_continuous_scanning_cb = did_end_continuous_scanning_cb;
    this->_will_cancel_scanning_cb = will_cancel_scanning_cb;
    this->_did_cancel_scanning_cb = did_cancel_scanning_cb;
    this->_did_complete_scanning_with_error_cb =
        did_complete_scanning_with_error_cb;
    this->_did_interrupt_scanning_with_error_cb =
        did_interrupt_scanning_with_error_cb;
    this->_will_warm_up_cb = will_warm_up_cb;
    this->_did_warm_up_cb = did_warm_up_cb;
    this->_network_did_request_start_scanning_cb =
        network_did_request_start_scanning_cb;
    this->_network_did_request_stop_scanning_cb =
        network_did_request_stop_scanning_cb;
    this->_did_disconnect_cb = did_disconnect_cb;
    this->_network_did_receive_server_error_cb =
        network_did_receive_server_error_cb;
    this->_network_should_prevent_timeout_cb =
        network_should_prevent_timeout_cb;
    this->_network_did_timeout_cb = network_did_timeout_cb;
    this->_is_reserved_by_host_cb = is_reserved_by_host_cb;
    this->_did_request_stop_cb = did_request_stop_cb;
    this->_did_request_push_scan_connection_cb =
        did_request_push_scan_connection_cb;
    this->_did_notify_status_change_cb = did_notify_status_change_cb;
  };

  void SetCtx(void* ctx);

  void ScannerDidEncounterDeviceCommunicationError(IESScanner* pScanner,
                                                   ESErrorCode err) override;
  void ScannerDidPressButton(UInt8 un8ButtonNumber) override;
  void ScannerWillBeginContinuousScanning(IESScanner* pScanner) override;
  void ScannerDidEndContinuousScanning(IESScanner* pScanner) override;
  void ScannerWillScanToScannedImage(IESScanner* pScanner,
                                     IESScannedImage* pESImage) override;
  void ScannerDidScanToScannedImage(IESScanner* pScanner,
                                    IESScannedImage* pESImage) override;
  void ScannerWillCancelScanning(IESScanner* pScanner) override;
  void ScannerDidCancelScanning(IESScanner* pScanner) override;
  void ScannerDidCompleteScanningWithError(IESScanner* pScanner,
                                           ESErrorCode err) override;
  void ScannerDidInterruptScanningWithError(IESScanner* pScanner,
                                            ESErrorCode err) override;
  void ScannerWillWarmUp(IESScanner* pScanner) override;
  void ScannerDidWarmUp(IESScanner* pScanner) override;
  void NetworkScannerDidRequestStartScanning(IESScanner* pScanner) override;
  void NetworkScannerDidRequestStopScanning(IESScanner* pScanner) override;
  void ScannerDidDisconnect(IESScanner* pScanner) override;
  void NetworkScannerDidReceiveServerError(IESScanner* pScanner) override;
  BOOL NetworkScannerShouldPreventTimeout(IESScanner* pScanner) override;
  void NetworkScannerDidTimeout(IESScanner* pScanner) override;
  void ScannerIsReservedByHost(IESScanner* pScanner,
                               const ES_CHAR* pszAddress) override;
  void ScannerDidRequestStop(IESScanner* pScanner) override;
  void ScannerDidRequestPushScanConnection(IESScanner* pScanner) override;
  void ScannerDidNotifyStatusChange(IESScanner* pScanner) override;
};

struct delegate {
  ScannerDelegate* obj;
  void* ctx;
};
