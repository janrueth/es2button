#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstring>

// these are from the epsonscan2 src
#include "ES2Command/IESScanner.h"
#include "common.hpp"
#include "internal.hpp"
#include "scanner.hpp"

#ifdef __cplusplus
extern "C" {
#endif

bool scanner_eq(scanner_t* a, scanner_t* b) { return a->obj == b->obj; }

void scanner_set_delegate(scanner_t* scanner, delegate_t* delegate) {
  if (scanner == NULL) {
    return;
  }
  scanner->owned_delegate = delegate;

  static_cast<IESScanner*>(scanner->obj)->SetDelegate(delegate->obj);
}

ESErrorCode scanner_set_connection(scanner_t* scanner, const char* json) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->SetConnection(json);
}

delegate_t* scanner_destroy_instance(scanner_t* scanner) {
  if (scanner == NULL) {
    return NULL;
  }

  static_cast<IESScanner*>(scanner->obj)->DestroyInstance();
  delegate_t* delegate = scanner->owned_delegate;
  scanner->owned_delegate = NULL;
  return delegate;
}

ESErrorCode scanner_open(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Open();
}

ESErrorCode scanner_close(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Close();
}

bool scanner_is_opened(scanner_t* scanner) {
  if (scanner == NULL) {
    return false;
  }

  return static_cast<IESScanner*>(scanner->obj)->IsOpened();
}

ESErrorCode scanner_scan(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Scan();
}

ESErrorCode scanner_scan_in_background(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->ScanInBackground();
}

ESErrorCode scanner_cancel(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Cancel();
}

ESErrorCode scanner_abort(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Abort();
}

bool scanner_is_scanning(scanner_t* scanner) {
  if (scanner == NULL) {
    return false;
  }

  return static_cast<IESScanner*>(scanner->obj)->IsScanning();
}

ESErrorCode scanner_do_cleaning(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->DoCleaning();
}

ESErrorCode scanner_do_calibration(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->DoCalibration();
}

bool scanner_is_interrupted(scanner_t* scanner) {
  if (scanner == NULL) {
    return false;
  }

  return static_cast<IESScanner*>(scanner->obj)->IsInterrupted();
}

bool scanner_is_afm_enabled(scanner_t* scanner) {
  if (scanner == NULL) {
    return false;
  }

  return static_cast<IESScanner*>(scanner->obj)->IsAfmEnabled();
}

ESErrorCode scanner_schedule_auto_feeding_mode_timeout(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)
      ->ScheduleAutoFeedingModeTimeout();
}

ESErrorCode scanner_start_job_in_mode(scanner_t* scanner, uint8_t eJobMode) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->StartJobInMode(eJobMode);
}

ESErrorCode scanner_stop_job_in_mode(scanner_t* scanner, uint8_t eJobMode) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->StopJobInMode(eJobMode);
}

ESErrorCode scanner_do_auto_focus(scanner_t* scanner, float* pfOutFocus) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->DoAutoFocus(pfOutFocus);
}

ESErrorCode scanner_set_panel_to_push_scan_ready(scanner_t* scanner,
                                                 bool bPushScanReady) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)
      ->SetPanelToPushScanReady(bPushScanReady);
}

bool scanner_is_scannable_device_config(scanner_t* scanner) {
  if (scanner == NULL) {
    return false;
  }

  return static_cast<IESScanner*>(scanner->obj)->IsScannableDeviceConfig();
}

ESErrorCode scanner_unlock_administrator_lock(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->UnlockAdministratorLock();
}

ESErrorCode scanner_lock_administrator_lock(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->LockAdministratorLock();
}

ESErrorCode scanner_reset(scanner_t* scanner) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->Reset();
}

ESErrorCode scanner_get_all_keys(scanner_t* scanner, char** oJSONStr) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err = static_cast<IESScanner*>(scanner->obj)->GetAllKeys(&res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();

  size_t required_len = strlen(cstr) + 1;
  *oJSONStr = (char*)malloc(required_len);

  memcpy(*oJSONStr, cstr, required_len);
  return err;
}

ESErrorCode scanner_get_default_value_for_key(scanner_t* scanner,
                                              const char* key,
                                              char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err =
      static_cast<IESScanner*>(scanner->obj)->GetDefaultValueForKey(key, &res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;

  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

ESErrorCode scanner_get_value_for_key(scanner_t* scanner, const char* key,
                                      char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err =
      static_cast<IESScanner*>(scanner->obj)->GetValueForKey(key, &res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;
  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

ESErrorCode scanner_set_value_for_key(scanner_t* scanner, const char* pszKey,
                                      const char* pszJSON) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)
      ->SetValueForKey(pszKey, pszJSON);
}

ESErrorCode scanner_set_values_with_JSON(scanner_t* scanner,
                                         const char* pszJSON) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  return static_cast<IESScanner*>(scanner->obj)->SetValuesWithJSON(pszJSON);
}

ESErrorCode scanner_get_all_values_for_key(scanner_t* scanner, const char* key,
                                           char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err =
      static_cast<IESScanner*>(scanner->obj)->GetAllValuesForKey(key, &res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;
  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

ESErrorCode scanner_get_all_values(scanner_t* scanner, char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err = static_cast<IESScanner*>(scanner->obj)->GetAllValues(&res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;
  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

ESErrorCode scanner_get_available_values_for_key(scanner_t* scanner,
                                                 const char* key,
                                                 char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err = static_cast<IESScanner*>(scanner->obj)
                        ->GetAvailableValuesForKey(key, &res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;
  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

ESErrorCode scanner_get_all_available_values(scanner_t* scanner,
                                             char** pstrResult) {
  if (scanner == NULL) {
    return ESErrorCode::kESErrorFatalError;
  }

  CESResultString res;
  ESErrorCode err =
      static_cast<IESScanner*>(scanner->obj)->GetAllAvailableValues(&res);
  if (err != kESErrorNoError) {
    return err;
  }

  const char* cstr = res.Get();
  size_t required_len = strlen(cstr) + 1;
  *pstrResult = (char*)malloc(required_len);
  memcpy(*pstrResult, cstr, required_len);

  return err;
}

#ifdef __cplusplus
}
#endif
