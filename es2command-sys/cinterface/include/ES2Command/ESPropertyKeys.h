// This file is copied from epsonscan2 6.7.43.0-1
// The imports have been modified to make them standalone
// The original file is licensed as LGPL 2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//! @file     ESPropertyKeys.h
//!
//! @brif     ES2Command 外部公開キーの定義
//! @note
//! @versoin  1.0
//! @par      Copyright SEIKO EPSON Corporation
//! @par      更新履歴
//! @par        - 新規作成       2014/12/25
//!
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "types.h"

//
// プロパティキー
//

//
// ※ Value :
// すべてのキーにおいて、コマンドが対応するキーだがスキャナー設定により現在サポートされない値の場合
// nullptrを返す
//

STATIC_CONST_KEY kESVersion =
    ES_STRING("version");  // Value            : [r] ESString
                           // AllValues        : ESString
                           // AvailableValues  :

STATIC_CONST_KEY kESWorkFolder =
    ES_STRING("workFolder");  // Value            : [rw] ESString
                              // AllValues        : nullptr
                              // AvailableValues  : nullptr

STATIC_CONST_KEY kESInterruptionEnabled = ES_STRING(
    "interruptionEnabled");  // Value            : [rw] bool
                             // AllValues        : ESIndexSet ( true, false )
                             // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESErrorStatus =
    ES_STRING("errorStatus");  // Value            : [r] ESNumber (ESErrorCode)
                               // AllValues        : nullptr
                               // AvailableValues  :

STATIC_CONST_KEY kESBatteryStatus =
    ES_STRING("batteryStatus");  // Value            : [r] ESNumber
                                 // (ESBatteryStatus) AllValues        : nullptr
                                 // AvailableValues  :

STATIC_CONST_KEY kESSensorGlassStatus =
    ES_STRING("sensorGlassStatus");  // Value            : [r] ESNumber
                                     // (ESSensorGlassStatus) AllValues        :
                                     // nullptr AvailableValues  :

STATIC_CONST_KEY kESScannerPositionStatus = ES_STRING(
    "scannerPositionStatus");  // Value            : [r] ESNumber
                               // (ENUM_ES_SCANNER_POSITION_STATUS) AllValues :
                               // nullptr AvailableValues  :

STATIC_CONST_KEY kESWarningStatus =
    ES_STRING("warningStatus");  // Value            : [r] ESNumber
                                 // (ENUM_ES_WARNING_STATUS) AllValues        :
                                 // nullptr AvailableValues  :

STATIC_CONST_KEY kESUnavailableScanParameterStatus = ES_STRING(
    "unavailableScanParameterStatus");  // Value            : [r] ESNumber
                                        // (ENUM_ES_UNAVAILABLE_SCAN_PARAMETER_STATUS)
                                        // AllValues        : nullptr
                                        // AvailableValues  :

STATIC_CONST_KEY kESAuthentication =
    ES_STRING("authentication");  // Value            : [r] bool
                                  // AllValues        : ESIndexSet ( true, false
                                  // ) AvailableValues  :

STATIC_CONST_KEY kESAuthenticationEnabled =
    ES_STRING("authenticationEnabled");  // Value            : [rw] bool
                                         // AllValues        : ESIndexSet (
                                         // true, false ) AvailableValues  :

STATIC_CONST_KEY kESLengthPadding =
    ES_STRING("lengthPadding");  // Value            : [r] bool
                                 // AllValues        : ESIndexSet ( true, false
                                 // ) AvailableValues  :

STATIC_CONST_KEY kESAutoFeedingMode =
    ES_STRING("autoFeedingMode");  // Value            : [r] bool
                                   // AllValues        : ESIndexSet ( true,
                                   // false ) AvailableValues  :

STATIC_CONST_KEY kESContinuousAutoFeedingMode =
    ES_STRING("continuousAutoFeedingMode");  // Value            : [r] bool
                                             // AllValues        : ESIndexSet (
                                             // true, false ) AvailableValues  :

STATIC_CONST_KEY kESAutoFeedingModeTimeout = ES_STRING(
    "autoFeedingModeTimeout");  // Value            : [rw] ESNumber (minutes)
                                // AllValues        : ST_ES_RANGE
                                // AvailableValues  : ST_ES_RANGE

STATIC_CONST_KEY kESProductName =
    ES_STRING("productName");  // Value            : [r] ESString
                               // AllValues        : ESString
                               // AvailableValues  :

STATIC_CONST_KEY kESSerialNumber =
    ES_STRING("serialNumber");  // Value            : [r] ESString
                                // AllValues        : ESString
                                // AvailableValues  :

STATIC_CONST_KEY kESAuthUsername =
    ES_STRING("authUsername");  // Value            : [rw] ESString
                                // AllValues        : nullptr
                                // AvailableValues  : nullptr

STATIC_CONST_KEY kESAuthPassword =
    ES_STRING("authPassword");  // Value            : [rw] ESString
                                // AllValues        : nullptr

STATIC_CONST_KEY kESDefaultPasswordType =
    ES_STRING("defaultPasswordType");  // Value            : [r] ESNumber
                                       // (ENUM_ES_DEFAULTPASSWORD_TYPE)
                                       // AllValues : nullptr AvailableValues  :

STATIC_CONST_KEY kESAdminLock =
    ES_STRING("adminLock");  // Value            : [r] bool
                             // AllValues        : ESIndexSet ( true, false )
                             // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESAdminLockEnabled = ES_STRING(
    "adminLockEnabled");  // Value            : [r] bool
                          // AllValues        : ESIndexSet ( true, false )
                          // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESAdminLockPassword =
    ES_STRING("adminLockPassword");  // Value            : [rw] ESString
                                     // AllValues        : nullptr
                                     // AvailableValues  : nullptr

STATIC_CONST_KEY kESFunctionalUnitType = ES_STRING(
    "functionalUnitType");  // Value            : [rw] ESNumber
                            // (ESFunctionalUnitType) AllValues        :
                            // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESXResolution =
    ES_STRING("xResolution");  // Value            : [rw] ESNumber
                               // AllValues        : ESIndexSet or ST_ES_RANGE
                               // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESYResolution =
    ES_STRING("yResolution");  // Value            : [rw] ESNumber
                               // AllValues        : ESIndexSet or ST_ES_RANGE
                               // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESOpticalResolution =
    ES_STRING("opticalResolution");  // Value            : [r] ESNumber
                                     // AllValues        : ESNumber
                                     // AvailableValues  : ESNumber

STATIC_CONST_KEY kESMaxScanSize =
    ES_STRING("maxScanSize");  // Value            : [r] ST_ES_SIZE_F
                               // AllValues        : ST_ES_SIZE_F
                               // AvailableValues  :

STATIC_CONST_KEY kESScanArea =
    ES_STRING("scanArea");  // Value            : [rw] ST_ES_RECT_F
                            // AllValues        : nullptr
                            // AvailableValues  : nullptr

STATIC_CONST_KEY kESScanAreaInPixel =
    ES_STRING("scanAreaInPixel");  // Value            : [rw] ST_ES_RECT_UN32
                                   // AllValues        : nullptr
                                   // AvailableValues  : nullptr

STATIC_CONST_KEY kESScanSize =
    ES_STRING("scanSize");  // Value            : [rw] ST_ES_SIZE_F
                            // AllValues        : nullptr
                            // AvailableValues  : nullptr

STATIC_CONST_KEY kESScanSizeInPixel =
    ES_STRING("scanSizeInPixel");  // Value            : [rw] ST_ES_SIZE_UN32
                                   // AllValues        : nullptr
                                   // AvailableValues  : nullptr

STATIC_CONST_KEY kESXOffsetMargin =
    ES_STRING("xOffsetMargin");  // Value            : [rw] ESFloat
                                 // AllValues        : nullptr
                                 // AvailableValues  : nullptr

STATIC_CONST_KEY kESYOffsetMargin =
    ES_STRING("yOffsetMargin");  // Value            : [rw] ESFloat
                                 // AllValues        : nullptr
                                 // AvailableValues  : nullptr

STATIC_CONST_KEY kESColorFormat =
    ES_STRING("colorFormat");  // Value            : [rw] ESNumber
                               // (ESColorFormat) AllValues        : ESIndexSet
                               // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESColorCounterType =
    ES_STRING("colorCounterType");  // Value            : [rw] ESNumber
                                    // (ENUM_ES_COLORCOUNTER_TYPE)

STATIC_CONST_KEY kESBitsPerPixel =
    ES_STRING("bitsPerPixel");  // Value            : [r] ESNumber
                                // AllValues        : nullptr
                                // AvailableValues  :

STATIC_CONST_KEY kESHalftone =
    ES_STRING("halftone");  // Value            : [rw] ESNumber (ESHalftone)
                            // AllValues        : ESIndexSet
                            // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESGammaMode =
    ES_STRING("gammaMode");  // Value            : [rw] ESNumber (ESGammaMode)
                             // AllValues        : ESIndexSet
                             // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESGammaTableMono =
    ES_STRING("gammaTableMono");  // Value            : [rw] ESIndexArray(256
                                  // array) or nullptr(get only)
STATIC_CONST_KEY kESGammaTableRed =
    ES_STRING("gammaTableRed");  // Value            : [rw] ESIndexArray(256
                                 // array) or nullptr(get only)
STATIC_CONST_KEY kESGammaTableGreen =
    ES_STRING("gammaTableGreen");  // Value            : [rw] ESIndexArray(256
                                   // array) or nullptr(get only)
STATIC_CONST_KEY kESGammaTableBlue =
    ES_STRING("gammaTableBlue");  // Value            : [rw] ESIndexArray(256
                                  // array) or nullptr(get only) AllValues :
                                  // nullptr AvailableValues  : nullptr

STATIC_CONST_KEY kESColorMatrix =
    ES_STRING("colorMatrix");  // Value            : [rw] ESFloatArray(3 x 3
                               // Floats) or nullptr(get only) AllValues :
                               // nullptr AvailableValues  : nullptr

STATIC_CONST_KEY kESThreshold =
    ES_STRING("threshold");  // Value            : [rw] ESNumber
                             // AllValues        : ESIndexSet or ST_ES_RANGE
                             // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESQuietMode =
    ES_STRING("quietMode");  // Value            : [rw] ESNumber (ESQuietMode)
                             // AllValues        : ESIndexSet
                             // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESBufferSize =
    ES_STRING("bufferSize");  // Value            : [rw] ESNumber
                              // AllValues        : nullptr
                              // AvailableValues  : nullptr

STATIC_CONST_KEY kESDuplexType =
    ES_STRING("duplexType");  // Value            : [r] ESNumber (ESDuplexType)
                              // AllValues        : ESNumber
                              // AvailableValues  :

STATIC_CONST_KEY kESDuplex =
    ES_STRING("duplex");  // Value            : [rw] bool
                          // AllValues        : ESIndexSet ( true, false )
                          // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESDoubleFeedDetection = ES_STRING(
    "doubleFeedDetection");  // Value            : [rw] ESNumber
                             // (ESDoubleFeedDetection) AllValues        :
                             // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESMinDoubleFeedDetectionRangeLength = ES_STRING(
    "minDoubleFeedDetectionRangeLength");  // Value    : [r] ESFloat (inches)
                                           // AllValues        : nullptr
                                           // AvailableValues  :

STATIC_CONST_KEY kESDoubleFeedDetectionRangeOffset = ES_STRING(
    "doubleFeedDetectionRangeOffset");  // Value        : [rw] ESFloat (inches)
                                        // AllValues        : nullptr
                                        // AvailableValues  : nullptr

STATIC_CONST_KEY kESDoubleFeedDetectionRangeLength = ES_STRING(
    "doubleFeedDetectionRangeLength");  // Value        : [rw] ESFloat (inches)
                                        // AllValues        : nullptr
                                        // AvailableValues  : nullptr

STATIC_CONST_KEY kESLenghtDoubleFeedDetection =
    ES_STRING("lengthDoubleFeedDetection");  // Value            : [rw] bool
                                             // AllValues        : ESIndexSet (
                                             // true, false ) AvailableValues  :
                                             // ESIndexSet ( true, false )

STATIC_CONST_KEY kESLengthDoubleFeedDetectionLength = ES_STRING(
    "lengthDoubleFeedDetectionLength");  // Value        : [rw] ESFloat (inches)
                                         // AllValues        : nullptr
                                         // AvailableValues  : nullptr

STATIC_CONST_KEY kESImageDoubleFeedDetection =
    ES_STRING("imageDoubleFeedDetection");  // Value            : [rw] bool
                                            // AllValues        : ESIndexSet (
                                            // true, false ) AvailableValues  :
                                            // ESIndexSet ( true, false )

STATIC_CONST_KEY kESImagePaperProtection = ES_STRING(
    "imagePaperProtection");  // Value            : [rw] bool
                              // AllValues        : ESIndexSet ( true, false )
                              // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESCarrierSheetDetection =
    ES_STRING("carrierSheetDeteciton");  // Value            : [r] bool
                                         // AllValues        : ESIndexSet (
                                         // true, false ) AvailableValues  :

STATIC_CONST_KEY kESAutoCropping =
    ES_STRING("autoCropping");  // Value            : [rw] bool
                                // AllValues        : ESIndexSet ( true, false )
                                // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESAutoCroppingInscribed = ES_STRING(
    "autoCroppingInscribed");  // Value            : [rw] bool
                               // AllValues        : ESIndexSet ( true, false )
                               // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESCroppableResolutions = ES_STRING(
    "croppableResolutions");  // Value        : [r] ESIndexSet or ST_ES_RANGE
                              // AllValues        : ESIndexSet or ST_ES_RANGE
                              // AvailableValues  :

STATIC_CONST_KEY kESCroppingSize = ES_STRING(
    "croppingSize");  // Value            : [rw] ESFloat
                      // AllValues        : ESFloatArray or ST_ES_RANGE_F
                      // AvailableValues  : ESFloatArray or ST_ES_RANGE_F

STATIC_CONST_KEY kESPagesToBeScanned =
    ES_STRING("pagesToBeScanned");  // Value            : [rw] ESNumber
                                    // AllValues        : nullptr
                                    // AvailableValues  : nullptr

STATIC_CONST_KEY kESDocumentLoaded =
    ES_STRING("documentLoaded");  // Value            : [r] bool
                                  // AllValues        : ESIndexSet ( true, false
                                  // ) AvailableValues  :

STATIC_CONST_KEY kESDocumentSeparation =
    ES_STRING("documentSeparation");  // Value            : [r] bool
                                      // AllValues        : ESIndexSet ( true,
                                      // false ) AvailableValues  :

STATIC_CONST_KEY kESCardScanning =
    ES_STRING("cardScanning");  // Value            : [r] bool
                                // AllValues        : ESIndexSet ( true, false )
                                // AvailableValues  :

STATIC_CONST_KEY kESCleaning =
    ES_STRING("cleaning");  // Value            : [r] bool
                            // AllValues        : ESIndexSet ( true, false )
                            // AvailableValues  :

STATIC_CONST_KEY kESCalibration =
    ES_STRING("calibration");  // Value            : [r] bool
                               // AllValues        : ESIndexSet ( true, false )
                               // AvailableValues  :

STATIC_CONST_KEY kESDetectedDocumentSize =
    ES_STRING("detectedDocumentSize");  // Value            : [r] ST_ES_SIZE_F
STATIC_CONST_KEY kESEdgeFillWidthRight =
    ES_STRING("edgeFillWidthRight");  // Value            : [rw] ESFloat
STATIC_CONST_KEY kESEdgeFillWidthTop =
    ES_STRING("edgeFillWidthTop");  // Value            : [rw] ESFloat
STATIC_CONST_KEY kESEdgeFillWidthLeft =
    ES_STRING("edgeFillWidthLeft");  // Value            : [rw] ESFloat
STATIC_CONST_KEY kESEdgeFillWidthBottom = ES_STRING(
    "edgeFillWidthBottom");  // Value            : [rw] ESFloat
                             // AllValues        : ESFloatArray or ST_ES_RANGE_F
                             // AvailableValues  : ESFloatArray or ST_ES_RANGE_F
                             // AllValues        : nullptr
                             // AvailableValues  :

STATIC_CONST_KEY kESEdgeFillColor =
    ES_STRING("edgeFillColor");  // Value            : [rw] ESNumber
                                 // (ESEdgeFillColor) AllValues        :
                                 // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESDigitalICE =
    ES_STRING("digitalICE");  // Value            : [rw] ESNumber (ESDigitalICE)
                              // AllValues        : ESIndexSet
                              // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESFilmType =
    ES_STRING("filmType");  // Value            : [rw] ESNumber (ESFilmType)
                            // AllValues        : ESIndexSet
                            // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESScanningMode =
    ES_STRING("scanningMode");  // Value            : [rw] ESNumber
                                // (ESScanningMode) AllValues        :
                                // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESLaminatedPaperMode = ES_STRING(
    "laminatedPaperMode");  // Value            : [rw] ESNumber
                            // (ESLaminatedPaperMode) AllValues        :
                            // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESBGColor =
    ES_STRING("BGColor");  // Value            : [rw] ESNumber
                           // (ENUM_ES_BG_COLOR) AllValues        : ESIndexSet
                           // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESWarmingUp =
    ES_STRING("warmingUp");  // Value            : [r] bool
                             // AllValues        : ESIndexSet ( true, false )
                             // AvailableValues  :

STATIC_CONST_KEY kESButtonStatus =
    ES_STRING("buttonStatus");  // Value            : [r] ESNumber
                                // AllValues        : nullptr
                                // AvailableValues  :

STATIC_CONST_KEY kESLampMode =
    ES_STRING("lampMode");  // Value            : [rw] ESNumber (ESLampMode)
                            // AllValues        : ESIndexSet
                            // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESPowerSaveTime =
    ES_STRING("powerSaveTime");  // Value            : [rw] ESNumber
                                 // (ENUM_ESCI_POWER_SAVE_TIME) AllValues :
                                 // ESIndexSet or ST_ES_RANGE AvailableValues  :
                                 // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESMaxFocus =
    ES_STRING("maxFocus");  // Value            : [r] ESFloat (mm)
                            // AllValues        : ESFloat
                            // AvailableValues  :

STATIC_CONST_KEY kESMinFocus =
    ES_STRING("minFocus");  // Value            : [r] ESFloat (mm)
                            // AllValues        : ESFloat
                            // AvailableValues  :

STATIC_CONST_KEY kESFocus =
    ES_STRING("focus");  // Value            : [rw] ESFloat (mm)
                         // AllValues        : nullptr
                         // AvailableValues  : nullptr

STATIC_CONST_KEY kESSimplexScanCounter =
    ES_STRING("simplexScanCounter");  // Value            : [rw] ESNumber
                                      // AllValues        : ESIndexSet or
                                      // ST_ES_RANGE or nullptr AvailableValues
                                      // : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESDuplexScanCounter =
    ES_STRING("duplexScanCounter");  // Value            : [rw] ESNumber
                                     // AllValues        : ESIndexSet or
                                     // ST_ES_RANGE or nullptr AvailableValues
                                     // : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESSimplexCardScanCounter = ES_STRING(
    "simplexCardScanCounter");  // Value            : [rw] ESNumber
                                // AllValues        : ESIndexSet or ST_ES_RANGE
                                // or nullptr AvailableValues  : ESIndexSet or
                                // ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESDuplexCardScanCounter = ES_STRING(
    "duplexCardScanCounter");  // Value            : [rw] ESNumber
                               // AllValues        : ESIndexSet or ST_ES_RANGE
                               // or nullptr AvailableValues  : ESIndexSet or
                               // ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESLamp1Counter =
    ES_STRING("lamp1Counter");  // Value            : [rw] ESNumber
STATIC_CONST_KEY kESLamp2Counter = ES_STRING(
    "lamp2Counter");  // Value            : [rw] ESNumber
                      // AllValues        : ESIndexSet or ST_ES_RANGE or nullptr
                      // AvailableValues  : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESPickupRollerCounter =
    ES_STRING("pickupRollerCounter");  // Value            : [rw] ESNumber
                                       // AllValues        : ESIndexSet or
                                       // ST_ES_RANGE or nullptr AvailableValues
                                       // : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESSeparationPadCounter = ES_STRING(
    "separationPadCounter");  // Value            : [rw] ESNumber
                              // AllValues        : ESIndexSet or ST_ES_RANGE or
                              // nullptr AvailableValues  : ESIndexSet or
                              // ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESRetardRollerCounter =
    ES_STRING("retardRollerCounter");  // Value            : [rw] ESNumber
                                       // AllValues        : ESIndexSet or
                                       // ST_ES_RANGE or nullptr AvailableValues
                                       // : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESScanCounter = ES_STRING(
    "scanCounter");  // Value            : [rw] ESNumber
                     // AllValues        : ESIndexSet or ST_ES_RANGE or nullptr
                     // AvailableValues  : ESIndexSet or ST_ES_RANGE or nullptr

STATIC_CONST_KEY kESCaptureCommandSupported =
    ES_STRING("captureCommandSupported");  // Value            : [rw] bool
                                           // AllValues        : ESIndexSet (
                                           // true, false ) AvailableValues  :
                                           // ESIndexSet ( true, false )

STATIC_CONST_KEY kESShouldIgnoreCancelFromScanner = ES_STRING(
    "shouldIgnoreCancelFromScanner");  // Value           : [rw] bool
                                       // AllValues        : ESIndexSet ( true,
                                       // false ) AvailableValues  : ESIndexSet
                                       // ( true, false )

STATIC_CONST_KEY kESGuidePosition =
    ES_STRING("guidePosition");  // Value            : [r] ESNumber
                                 // (ESGuidePosition) AllValues        :
                                 // ESIndexSet AvailableValues  :

STATIC_CONST_KEY kESGuidePositionFB =
    ES_STRING("guidePositionFB");  // Value            : [rw] ESNumber
                                   // (ESGuidePosition) AllValues        :
                                   // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESGuidePositionADF =
    ES_STRING("guidePositionADF");  // Value            : [rw] ESNumber
                                    // (ESGuidePosition) AllValues        :
                                    // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESGuidelessADF =
    ES_STRING("guidelessADF");  // Value            : [r] bool

STATIC_CONST_KEY kESDisableJobContinue = ES_STRING(
    "disableJobContinue");  // Value            : [rw] bool
                            // AllValues        : ESIndexSet ( true, false )
                            // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESDisableKeepingCapture = ES_STRING(
    "disableKeepingCapture");  // Value            : [rw] bool
                               // AllValues        : ESIndexSet ( true, false )
                               // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESMaxImagePixels =
    ES_STRING("maxImagePixels");  // Value            : [r] ST_ES_SIZE_F
                                  // AllValues        : ST_ES_SIZE_F
                                  // AvailableValues  :

STATIC_CONST_KEY kESMaxScanSizeInLongLength = ES_STRING(
    "maxScanSizeInLongLength");  // Value            : [ESCI: rw, ESCI/2: r]
                                 // ST_ES_SIZE_F AllValues        : ST_ES_SIZE_F
                                 // AvailableValues  : nullptr

STATIC_CONST_KEY kESMaxLongLengthTable =
    ES_STRING("maxLongLengthTable");  // Value            : [r] ESDictionary
                                      // AllValues        : ESDicArray
                                      // AvailableValues  : nullptr

STATIC_CONST_KEY kESMinScanSize =
    ES_STRING("minScanSize");  // Value            : [r] ST_ES_SIZE_F
                               // AllValues        : ST_ES_SIZE_F
                               // AvailableValues  :

STATIC_CONST_KEY kESImageFormat =
    ES_STRING("imageFormat");  // Value            : [rw] ESNumber
                               // (ESImageFormat) AllValues        : ESIndexSet
                               // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESColorMatrixMode =
    ES_STRING("colorMatrixMode");  // Value            : [rw] ESNumber
                                   // (ESColorMatrixMode) AllValues        :
                                   // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESSkewCorrection =
    ES_STRING("skewCorrection");  // Value            : [rw] bool
                                  // AllValues        : ESIndexSet ( true, false
                                  // ) AvailableValues  : ESIndexSe

STATIC_CONST_KEY kESJPEGQuality =
    ES_STRING("JPEGQuality");  // Value            : [rw] ESNumber
                               // AllValues        : ESIndexSet or ST_ES_RANGE
                               // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPaperEndDetection = ES_STRING(
    "paperEndDetection");  // Value            : [rw] bool
                           // AllValues        : ESIndexSet or ST_ES_RANGE
                           // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESOverScan =
    ES_STRING("overScan");  // Value            : [rw] bool
                            // AllValues        : ESIndexSet ( true, false )
                            // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESOverScanForCropping = ES_STRING(
    "overScanForCropping");  // Value            : [rw] bool
                             // AllValues        : ESIndexSet ( true, false )
                             // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESPassportCarrierSheetScan =
    ES_STRING("passportCarrierSheetScan");  // Value            : [rw] bool
                                            // AllValues        : ESIndexSet (
                                            // true, false ) AvailableValues  :
                                            // ESIndexSet ( true, false )

STATIC_CONST_KEY kESPowerOffTime =
    ES_STRING("powerOffTime");  // Value            : [rw] ESNumber(min)
STATIC_CONST_KEY kESPowerOffTime2nd = ES_STRING(
    "powerOffTime2nd");  // Value            : [rw] ESNumber(min)
                         // AllValues        : ESIndexSet or ST_ES_RANGE
                         // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESFirstPCConnectionDate = ES_STRING(
    "firstPCConnectionDate");  // Value            : [r] ESString  ("%Y-%m-%d
                               // %H:%M" in UTC) AllValues        : ESIndexSet
                               // or ST_ES_RANGE AvailableValues

STATIC_CONST_KEY kESDocumentFeederLamp1Counter = ES_STRING(
    "documentFeederLamp1Counter");  // Value            : [rw] ESNumber
STATIC_CONST_KEY kESDocumentFeederLamp2Counter = ES_STRING(
    "documentFeederLamp2Counter");  // Value            : [rw] ESNumber
                                    // AllValues        : ESIndexSet or
                                    // ST_ES_RANGE AvailableValues  : ESIndexSet
                                    // or ST_ES_RANGE

STATIC_CONST_KEY kESPaperJamCounter = ES_STRING(
    "paperJamCounter");  // Value            : [rw] ESNumber
                         // AllValues        : ESIndexSet or ST_ES_RANGE
                         // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESUltraSonicDoubleFeedCounter = ES_STRING(
    "ultraSonicDoubleFeedCounter");  // Value            : [rw] ESNumber
                                     // AllValues        : ESIndexSet or
                                     // ST_ES_RANGE AvailableValues  :
                                     // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESLengthDoubleFeedCounter = ES_STRING(
    "lengthDoubleFeedCounter");  // Value            : [rw] ESNumber
                                 // AllValues        : ESIndexSet or ST_ES_RANGE
                                 // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESRollerKitCounter = ES_STRING(
    "rollerKitCounter");  // Value            : [rw] ESNumber
                          // AllValues        : ESIndexSet or ST_ES_RANGE
                          // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESImageDoubleFeedCounter = ES_STRING(
    "imageDoubleFeedCounter");  // Value            : [rw] ESNumber
                                // AllValues        : ESIndexSet or ST_ES_RANGE
                                // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPaperProtectionCounter = ES_STRING(
    "paperProtectionCounter");  // Value            : [rw] ESNumber
                                // AllValues        : ESIndexSet or ST_ES_RANGE
                                // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPaperProtectionOverflowCounter = ES_STRING(
    "paperProtectionOverflowCounter");  // Value            : [rw] ESNumber
                                        // AllValues        : ESIndexSet or
                                        // ST_ES_RANGE AvailableValues  :
                                        // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPaperProtectionDistortionCounter = ES_STRING(
    "paperProtectionDistortionCounter");  // Value            : [rw] ESNumber
                                          // AllValues        : ESIndexSet or
                                          // ST_ES_RANGE AvailableValues  :
                                          // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESSpecialDocumentCounter = ES_STRING(
    "specialDocumentCounter");  // Value            : [rw] ESNumber
                                // AllValues        : ESIndexSet or ST_ES_RANGE
                                // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPassportCarrierSheetCounter = ES_STRING(
    "passportCarrierSheetCounter");  // Value            : [rw] ESNumber
                                     // AllValues        : ESIndexSet or
                                     // ST_ES_RANGE AvailableValues  :
                                     // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESFlatbedLamp1Counter =
    ES_STRING("flatbedLamp1Counter");  // Value            : [rw] ESNumber
STATIC_CONST_KEY kESFlatbedLamp2Counter = ES_STRING(
    "flatbedLamp2Counter");  // Value            : [rw] ESNumber
                             // AllValues        : ESIndexSet or ST_ES_RANGE
                             // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESDocumentTopCorrectionFront = ES_STRING(
    "documentTopCorrectionFront");  // Value            : [rw] ESFloat (1/1000
                                    // inch) AllValues        : ESFloatArray or
                                    // ST_ES_RANGE_F AvailableValues  :
                                    // ESFloatArray or ST_ES_RANGE_F

STATIC_CONST_KEY kESDocumentTopCorrectionBack = ES_STRING(
    "documentTopCorrectionBack");  // Value            : [rw] ESFloat (1/1000
                                   // inch) AllValues        : ESFloatArray or
                                   // ST_ES_RANGE_F AvailableValues  :
                                   // ESFloatArray or ST_ES_RANGE_F

STATIC_CONST_KEY kESDocumentDriveCorrectionFront = ES_STRING(
    "documentDriveCorrectionFront");  // Value            : [rw] ESFloat %単位
                                      // AllValues        : ESFloatArray or
                                      // ST_ES_RANGE_F AvailableValues  :
                                      // ESFloatArray or ST_ES_RANGE_F

STATIC_CONST_KEY kESDocumentDriveCorrectionBack = ES_STRING(
    "documentDriveCorrectionBack");  // Value            : [rw] ESFloat %単位
                                     // AllValues        : ESFloatArray or
                                     // ST_ES_RANGE_F AvailableValues  :
                                     // ESFloatArray or ST_ES_RANGE_F

STATIC_CONST_KEY kESLightIntensityBack = ES_STRING(
    "lightIntensityBack");  // Value            : [rw] ESNumber
                            // AllValues        : ESIndexSet or ST_ES_RANGE
                            // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESLightIntensityFB = ES_STRING(
    "lightIntensityFB");  // Value            : [rw] ESNumber
                          // AllValues        : ESIndexSet or ST_ES_RANGE
                          // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESDocumentFeederBGLevelFront = ES_STRING(
    "documentFeederBGLevelFront");  // Value            : [r] ESDictionary
                                    // (BGLevel Dictionary) AllValues        :
                                    // nullptr AvailableValues  :

STATIC_CONST_KEY kESDocumentFeederBGLevelBack = ES_STRING(
    "documentFeederBGLevelBack");  // Value            : [r] ESDictionary
                                   // (BGLevel Dictionary) AllValues        :
                                   // nullptr AvailableValues  :

STATIC_CONST_KEY kESPickupRollerLifeLimit =
    ES_STRING("pickupRollerLifeLimit");  // Value            : [r] ESNumber
                                         // AllValues        : nullptr
                                         // AvailableValues  :

STATIC_CONST_KEY kESSeparationPadLifeLimit =
    ES_STRING("separationPadLifeLimit");  // Value            : [r] ESNumber
                                          // AllValues        : nullptr
                                          // AvailableValues  :

STATIC_CONST_KEY kESRollerKitLifeLimit =
    ES_STRING("rollerKitLifeLimit");  // Value            : [r] ESNumber
                                      // AllValues        : nullptr
                                      // AvailableValues  :

STATIC_CONST_KEY kESRetardRollerLifeLimit =
    ES_STRING("retardRollerLifeLimit");  // Value            : [r] ESNumber
                                         // AllValues        : nullptr
                                         // AvailableValues  :

STATIC_CONST_KEY kESPickupRollerNearend =
    ES_STRING("pickupRollerNearend");  // Value            : [r] ESNumber
                                       // AllValues        : nullptr
                                       // AvailableValues  :

STATIC_CONST_KEY kESSeparationPadNearend =
    ES_STRING("separationPadNearend");  // Value            : [r] ESNumber
                                        // AllValues        : nullptr
                                        // AvailableValues  :

STATIC_CONST_KEY kESRetardRollerNearend =
    ES_STRING("retardRollerNearend");  // Value            : [r] ESNumber
                                       // AllValues        : nullptr
                                       // AvailableValues  :

STATIC_CONST_KEY kESRollerKitNearend =
    ES_STRING("rollerKitNearend");  // Value            : [r] ESNumber
                                    // AllValues        : nullptr
                                    // AvailableValues  :

STATIC_CONST_KEY kESSensorGlassDirtSensitivity = ES_STRING(
    "sensorGlassDirtSensitivity");  // Value            : [rw] ESNumber
                                    // (ESSensorGlassDirtSensitivity) AllValues
                                    // : ESIndexSet AvailableValues  :
                                    // ESIndexSet

STATIC_CONST_KEY kESClientApplication =
    ES_STRING("clientApplication");  // Value            : [rw] ESNumber
                                     // (ESClientApplication) AllValues        :
                                     // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESDirectPowerOn =
    ES_STRING("directPowerOn");  // Value            : [rw] ESNumber
                                 // (ENUM_ES_DIRECTPOWERON_MODE) AllValues :
                                 // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESNonConnectPowerOff = ES_STRING(
    "nonConnectPowerOff");  // Value            : [rw] ESNumber
                            // (ENUM_ES_NONCONNECTPOWEROFF_MODE) AllValues :
                            // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESADFPaperProtection = ES_STRING(
    "adfPaperProtection");  // Value            : [rw] ESNumber
                            // (ENUM_ES_ADFPAPERPROTECTION_MODE) AllValues :
                            // ESIndexSet AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESBehaviorWhenDoubleFeed = ES_STRING(
    "behaviorWhenDoubleFeed");  // Value            : [rw] ESNumber
                                // (ENUM_ES_BEHAVIORWHENDOUBLEFEED_MODE)
                                // AllValues        : ESIndexSet
                                // AvailableValues  : ESIndexSet

STATIC_CONST_KEY kESCleaningWarningNotifyCount = ES_STRING(
    "cleaningWarningNotifyCount");  // Value            : [rw] ESNumber
                                    // AllValues        : ESIndexSet or
                                    // ST_ES_RANGE AvailableValues  : ESIndexSet
                                    // or ST_ES_RANGE

STATIC_CONST_KEY kESRollerKitNotifyCount = ES_STRING(
    "rollerKitNotifyCount");  // Value            : [rw] ESNumber
                              // AllValues        : ESIndexSet or ST_ES_RANGE
                              // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESRetardRollerNotifyCount = ES_STRING(
    "retardRollerNotifyCount");  // Value            : [rw] ESNumber
                                 // AllValues        : ESIndexSet or ST_ES_RANGE
                                 // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESSeparationPadNotifyCount =
    ES_STRING("separationPadNotifyCount");  // Value            : [rw] ESNumber
                                            // AllValues        : ESIndexSet or
                                            // ST_ES_RANGE AvailableValues  :
                                            // ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESPickupRollerNotifyCount = ES_STRING(
    "pickupRollerNotifyCount");  // Value            : [rw] ESNumber
                                 // AllValues        : ESIndexSet or ST_ES_RANGE
                                 // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESCleaningWarningCounter = ES_STRING(
    "cleaningWarningCounter");  // Value            : [rw] ESNumber
                                // AllValues        : ESIndexSet or ST_ES_RANGE
                                // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESCleaningWarningNotify = ES_STRING(
    "cleaningWarningNotify");  // Value            : [rw] ESNumber
                               // AllValues        : ESIndexSet or ST_ES_RANGE
                               // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESDetectColorTypeEnabled = ES_STRING(
    "detectColorTypeEnabled");  // Value            : [rw] bool
                                // AllValues        : ESIndexSet ( true, false )
                                // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESDetectBlankPageEnabled = ES_STRING(
    "detectBlankPageEnabled");  // Value            : [rw] bool
                                // AllValues        : ESIndexSet ( true, false )
                                // AvailableValues  : ESIndexSet ( true, false )

STATIC_CONST_KEY kESDetectBlankPageLevel = ES_STRING(
    "detectBlankPageLevel");  // Value			: Integer
                              // AllValues        : ESIndexSet or ST_ES_RANGE
                              // AvailableValues  : ESIndexSet or ST_ES_RANGE

STATIC_CONST_KEY kESSkipImageEnhancement = ES_STRING(
    "skipImageEnhancement");  // Value            : [rw] bool
                              // AllValues        : ESIndexSet ( true, false )
                              // AvailableValues  : ESIndexSet ( true, false )

//
// kESDocumentFeederBGLevelFront,
// kESDocumentFeederBGLevelBackで取得される辞書内のキー。
//
STATIC_CONST_KEY kESBGLevelKeyRed = ES_STRING("bgLevelKeyRed");  // r   ESNumber
STATIC_CONST_KEY kESBGLevelKeyRedWidth =
    ES_STRING("bgLevelKeyRedWidth");  // r   ESNumber
STATIC_CONST_KEY kESBGLevelKeyGreen =
    ES_STRING("bgLevelKeyGreen");  // r   ESNumber
STATIC_CONST_KEY kESBGLevelKeyGreenWidth =
    ES_STRING("bgLevelKeyGreenWidth");  // r   ESNumber
STATIC_CONST_KEY kESBGLevelKeyBlue = ES_STRING("bgLevelKeyBlue");  // r ESNumber
STATIC_CONST_KEY kESBGLevelKeyBlueWidth =
    ES_STRING("bgLevelKeyBlueWidth");  // r   ESNumber
STATIC_CONST_KEY kESBGLevelKeyMono = ES_STRING("bgLevelKeyMono");  // r ESNumber
STATIC_CONST_KEY kESBGLevelKeyMonoWidth =
    ES_STRING("bgLevelKeyMonoWidth");  // r   ESNumber

// Image processing Keys
STATIC_CONST_KEY kESBackgroundRemoval = ES_STRING(
    "backgroundRemoval");  // rw    ESNumber (ENUM_ES_BACKGROUNDREMOVAL_LEVEL)
STATIC_CONST_KEY kESBrightness =
    ES_STRING("brightness");  // rw    ESNumber [-100 ~ 100]
STATIC_CONST_KEY kESContrast =
    ES_STRING("contrast");  // rw    ESNumber [-100 ~ 100]
STATIC_CONST_KEY kESGammaScale =
    ES_STRING("gammaScale");  // rw    ESNumber [5 ~ 30]
STATIC_CONST_KEY kESSharpnessFilter = ES_STRING(
    "sharpnessFilterLevel");  // rw    ESNumber (ENUM_ES_SHARPNESSFILTER_LEVEL)
STATIC_CONST_KEY kESADFLoadSupported = ES_STRING("adfLoadSupported");