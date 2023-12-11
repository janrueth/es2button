#include "wrapper.hpp"

#include <stdint.h>

#include "ES2Command/ES2CommandAPI.h"
#include "ES2Command/ESCommandProperties.h"
#include "internal.hpp"

#ifdef __cplusplus
extern "C" {
#endif

ESErrorCode scanner_create(PFN_CREATE_SCANNER fptr, ESCommandType commandType,
                           scanner_t** ppScanner) {
  *ppScanner = (scanner_t*)malloc(sizeof(scanner_t));
  return fptr(commandType, &((*ppScanner)->obj));
}

void scanner_free(scanner_t* scanner) { free(scanner); }

#ifdef __cplusplus
}
#endif
