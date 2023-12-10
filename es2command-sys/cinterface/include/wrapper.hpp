#include "ES2Command/ES2CommandAPI.h"
#include "ES2Command/ESCommandProperties.h"
#include "ES2Command/ESPropertyKeys.h"
#include "common.hpp"
#include "delegate.hpp"
#include "scanner.hpp"

// INSTALL_LIB_DIR is passed as a cmd line argument from the build script
static const char DEFAULT_INSTALL_LIB_DIR[] = INSTALL_LIB_DIR "/epsonscan2";
static const char DEFAULT_ES_CREATE_SCANNER_SYMBOL_NAME[] = "ESCreateScanner";

#ifdef __cplusplus
extern "C" {
#endif

ESErrorCode scanner_create(PFN_CREATE_SCANNER fptr, ESCommandType commandType,
                           scanner_t** ppScanner);

void scanner_free(scanner_t* scanner);

#ifdef __cplusplus
}
#endif
