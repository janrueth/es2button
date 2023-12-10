#pragma once

#include <stddef.h>
#include <stdint.h>

#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

bool scanner_eq(scanner_t* a, scanner_t* b);
void scanner_set_delegate(scanner_t* scanner, delegate_t* delegate);
ESErrorCode scanner_set_connection(scanner_t* scanner, const char* json);

delegate_t* scanner_destroy_instance(scanner_t* scanner);
ESErrorCode scanner_open(scanner_t* scanner);

ESErrorCode scanner_close(scanner_t* scanner);

bool scanner_is_opened(scanner_t* scanner);

ESErrorCode scanner_scan(scanner_t* scanner);

ESErrorCode scanner_scan_in_background(scanner_t* scanner);

ESErrorCode scanner_cancel(scanner_t* scanner);
ESErrorCode scanner_abort(scanner_t* scanner);
bool scanner_is_scanning(scanner_t* scanner);
ESErrorCode scanner_do_cleaning(scanner_t* scanner);

ESErrorCode scanner_do_calibration(scanner_t* scanner);

bool scanner_is_interrupted(scanner_t* scanner);

bool scanner_is_afm_enabled(scanner_t* scanner);

ESErrorCode scanner_schedule_auto_feeding_mode_timeout(scanner_t* scanner);

ESErrorCode scanner_start_job_in_mode(scanner_t* scanner, uint8_t eJobMode);

ESErrorCode scanner_stop_job_in_mode(scanner_t* scanner, uint8_t eJobMode);

ESErrorCode scanner_do_auto_focus(scanner_t* scanner, float* pfOutFocus);

ESErrorCode scanner_set_panel_to_push_scan_ready(scanner_t* scanner,
                                                 bool bPushScanReady);

bool scanner_is_scannable_device_config(scanner_t* scanner);

ESErrorCode scanner_unlock_administrator_lock(scanner_t* scanner);

ESErrorCode scanner_lock_administrator_lock(scanner_t* scanner);

ESErrorCode scanner_reset(scanner_t* scanner);

ESErrorCode scanner_get_all_keys(scanner_t* scanner, char** oJSONStr);
ESErrorCode scanner_get_default_value_for_key(scanner_t* scanner,
                                              const char* key,
                                              char** pstrResult);

ESErrorCode scanner_get_value_for_key(scanner_t* scanner, const char* key,
                                      char** pstrResult);
ESErrorCode scanner_set_value_for_key(scanner_t* scanner, const char* pszKey,
                                      const char* pszJSON);

ESErrorCode scanner_set_values_with_JSON(scanner_t* scanner,
                                         const char* pszJSON);

ESErrorCode scanner_get_all_values_for_key(scanner_t* scanner, const char* key,
                                           char** pstrResult);

ESErrorCode scanner_get_all_values(scanner_t* scanner, char** pstrResult);

ESErrorCode scanner_get_available_values_for_key(scanner_t* scanner,
                                                 const char* key,
                                                 char** pstrResult);
ESErrorCode scanner_get_all_available_values(scanner_t* scanner,
                                             char** pstrResult);

#ifdef __cplusplus
}
#endif