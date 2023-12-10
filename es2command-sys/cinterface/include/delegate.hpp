#pragma once

#include <stdint.h>

#include "ES2Command/ESCommandProperties.h"
#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*delegate_cb)(void*, scanner_t*);
typedef bool (*delegate_cb_ret_bool)(void*, scanner_t*);
typedef void (*delegate_cb_with_error_code)(void*, scanner_t*, ESErrorCode);
typedef void (*delegate_cb_with_cstr)(void*, scanner_t*, const char*);
typedef void (*delegate_cb_with_button)(void*, uint8_t);

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
    delegate_cb did_notify_status_change_cb);

void delegate_free(delegate_t* obj);

#ifdef __cplusplus
}
#endif