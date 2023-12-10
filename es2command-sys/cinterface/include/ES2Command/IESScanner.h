// This file is copied from epsonscan2 6.7.43.0-1
// The imports have been modified to make them standalone
// The actual interfaces remain untouched
////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//! @file     IESScanner.h
//!
//! @brif     スキャナ操作インターフェース クラス
//! @note
//! @versoin  1.0
//! @par      Copyright SEIKO EPSON Corporation
//! @par      更新履歴
//! @par        - 新規作成       2014/12/25
//!
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define CALLBACK

#include "ESCommandProperties.h"
#include "ESResultString.h"
#include "types.h"

class IESScanner;
class IESScannedImage;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// [ IESScannerDelegate ]
//
// @brif スキャン結果を受け取る Delegate クラスのインターフェース
//       DLL利用側で、IESScannerにセットする。
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IESScannerDelegate {
 public:
  /**
   連続する一連のスキャンの開始を通知する。
   連続するスキャンは、ADFでの間断ないスキャンを指す。
   */
  virtual void CALLBACK
  ScannerWillBeginContinuousScanning(IESScanner* pScanner) = 0;

  /**
   連続する一連のスキャンの終了を通知する。
   連続するスキャンは、ADFでの間断ないスキャンを指す。
   */
  virtual void CALLBACK
  ScannerDidEndContinuousScanning(IESScanner* pScanenr) = 0;

  /**
   1ページ分のスキャン開始を通知する。
   */
  virtual void CALLBACK ScannerWillScanToScannedImage(
      IESScanner* pScanner, IESScannedImage* pESImage) = 0;

  /**
   1ページ分のスキャン終了を通知する。
   */
  virtual void CALLBACK ScannerDidScanToScannedImage(
      IESScanner* pScanner, IESScannedImage* pESImage) = 0;

  /**
   スキャンのキャンセルが行われることを通知する。
   */
  virtual void CALLBACK ScannerWillCancelScanning(IESScanner* pScanner) = 0;

  /**
   スキャンのキャンセルを通知する。
   */
  virtual void CALLBACK ScannerDidCancelScanning(IESScanner* pScanner) = 0;

  /**
   スキャンの完了を通知する。
   AFM有効時はAFMの終了時のみ発行され、それ以外では発行されない。
   */
  virtual void CALLBACK ScannerDidCompleteScanningWithError(
      IESScanner* pScanner, ESErrorCode err) = 0;

  /**
   エラーによるスキャンの中断を通知する。
   */
  virtual void CALLBACK ScannerDidInterruptScanningWithError(
      IESScanner* pcScanner, ESErrorCode err) = 0;

  /**
    通信エラーを通知する。
   */
  virtual void CALLBACK ScannerDidEncounterDeviceCommunicationError(
      IESScanner* pScanner, ESErrorCode err) = 0;

  /**
   ウォームアップ開始を通知する。
   */
  virtual void CALLBACK ScannerWillWarmUp(IESScanner* pScanner) = 0;

  /**
   ウォームアップ終了を通知する。
   */
  virtual void CALLBACK ScannerDidWarmUp(IESScanner* pScanner) = 0;

  virtual void CALLBACK
  NetworkScannerDidRequestStartScanning(IESScanner* pScanner) = 0;

  virtual void CALLBACK
  NetworkScannerDidRequestStopScanning(IESScanner* pScanner) = 0;

  virtual void CALLBACK ScannerDidDisconnect(IESScanner* pScanner) = 0;

  virtual void CALLBACK
  NetworkScannerDidReceiveServerError(IESScanner* pScanner) = 0;

  virtual BOOL CALLBACK
  NetworkScannerShouldPreventTimeout(IESScanner* pScanner) = 0;

  virtual void CALLBACK NetworkScannerDidTimeout(IESScanner* pScanner) = 0;

  /**
   ネットワークスキャナーが別のクライアントによって使用されていることを通知する。
   */
  virtual void CALLBACK ScannerIsReservedByHost(IESScanner* pScanner,
                                                const ES_CHAR* pszAddress) = 0;

  /**
   スキャナーのプッシュスキャンボタンが押されたことを通知する。
   */
  virtual void CALLBACK ScannerDidPressButton(UInt8 un8ButtonNumber) = 0;
  /**
   スキャナーのストップボタンが押されたことを通知する。
   */
  virtual void CALLBACK ScannerDidRequestStop(IESScanner* pScanner) = 0;

  /**
   スキャナーがプッシュスキャン（ジョブ情報）を要求したことを通知する。
  */
  virtual void CALLBACK
  ScannerDidRequestPushScanConnection(IESScanner* pScanner) = 0;

  /**
   スキャナーの状態（姿勢・分離レバー）が変化したことを通知する。
   */
  virtual void CALLBACK ScannerDidNotifyStatusChange(IESScanner* pScanner) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// [ IESScanner ]
//
// @brif スキャナ操作インターフェースクラス
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IESScanner {
 public:
  //==============================================================================================
  //
  // 初期化・終了処理
  //
  //==============================================================================================

  //
  // スキャン時のプロセス処理を行うDelegateを設定する
  //
  virtual void SetDelegate(IESScannerDelegate* pDelegate) = 0;

  //
  // スキャナとの接続設定を行う
  //  設定値は下記のJSONフォーマット文字列を渡す
  //
  // 【 ローカル接続  kESConnectionLocal 】
  //
  // {
  //   "ConnectionSetting" : [
  //        {
  //           "ConnectType" :{
  //             "int" : 0,
  //           },
  //           "InternalName" : {
  //      	   "string" : "デバイス名(DeviceInternalName)"
  //           }
  //       }
  //    ]
  // }
  //
  // 【 ネットワーク接続  kESConnectionNetworkIS | kESConnectionNetworkNT 】
  //
  // {
  //   "ConnectionSetting" : [
  //        {
  //           "ConnectType" :{
  //             "int" : 1     // ISプロトコルの場合
  //           }
  //           "Address" : {
  //      	   "string" : "IPアドレス" または"ホスト名"
  //           }
  //           "ConnectionTimeout" : {  // 接続タイムアウト時間(秒）[オプション]
  //      	   "int" : 30
  //           }
  //           "CommunicationTimeout" : {  //
  //           通信タイムアウト時間(秒）[オプション]
  //      	   "int" : 30
  //           }
  //       }
  //    ]
  // }
  //
  //
  virtual ESErrorCode SetConnection(ES_JSON_CPTR pszJSON) = 0;

  //
  // クラスインスタンスを破壊します。
  //
  virtual void DestroyInstance() = 0;

  //==============================================================================================
  //
  // オープン・クローズ
  //
  //==============================================================================================

  //
  // スキャナとの通信を開始する。
  //
  virtual ESErrorCode Open() = 0;

  //
  // スキャナとの通信を終了する
  //
  virtual ESErrorCode Close() = 0;

  //
  // スキャナがオープンしているか？
  //
  virtual bool IsOpened() const = 0;

  //==============================================================================================
  //
  // スキャン操作
  //
  //==============================================================================================

  //
  // 現在のスキャン設定でスキャンを開始する。
  //
  virtual ESErrorCode Scan() = 0;

  //
  // 別スレッドでスキャンを開始する。
  //
  virtual ESErrorCode ScanInBackground() = 0;

  //
  // スキャン処理をキャンセルする。
  // キャンセル成功時には、DidCompleteScanningWithErrorにて通知される
  //
  virtual ESErrorCode Cancel() = 0;

  //
  //
  //
  virtual ESErrorCode Abort() = 0;

  //
  // スキャン中か？
  //
  virtual bool IsScanning() const = 0;

  //==============================================================================================
  //
  // メンテナンス操作
  //
  //==============================================================================================

  //
  // スキャナセンサーのクリーニング動作を要求する。
  //
  virtual ESErrorCode DoCleaning() = 0;

  //
  // スキャナセンサーのキャリブレーションを要求する。
  //
  virtual ESErrorCode DoCalibration() = 0;

  //==============================================================================================
  //
  // AutoFeedingMode操作
  //
  //==============================================================================================

  //
  // 中断中か？
  //
  virtual bool IsInterrupted() const = 0;

  //
  // AFM中か？
  //
  virtual bool IsAfmEnabled() const = 0;

  //
  // Auto Feeding Mode タイムアウトチェック開始
  //
  virtual ESErrorCode ScheduleAutoFeedingModeTimeout() = 0;

  //==============================================================================================
  //
  // ジョブリクエスト
  //
  //==============================================================================================

  //
  // スキャンジョブの開始
  //
  virtual ESErrorCode StartJobInMode(ESJobMode eJobMode) = 0;

  //
  // スキャンジョブの終了
  //
  virtual ESErrorCode StopJobInMode(ESJobMode eJobMode) = 0;

  //==============================================================================================
  //
  // その他
  //
  //==============================================================================================

  //
  // オートフォーカスを要求する。
  // @param pfOutFocus
  // オートフォーカスの結果として焦点位置を受け取るバッファへのポインタ。単位はmm。
  // @return エラーコード。
  //
  virtual ESErrorCode DoAutoFocus(ESFloat* pfOutFocus) = 0;

  //
  // スキャナーパネルのプッシュスキャン可能状態を設定する
  //
  virtual ESErrorCode SetPanelToPushScanReady(BOOL bPushScanReady) = 0;

  virtual BOOL IsScannableDeviceConfig() = 0;

  //
  // パスワード
  //
  virtual ESErrorCode UnlockAdministratorLock() = 0;
  virtual ESErrorCode LockAdministratorLock() = 0;

  //==============================================================================================
  //
  // スキャナ情報
  //
  //==============================================================================================

  //
  // 設定をリセットする
  //
  virtual ESErrorCode Reset() = 0;

  //
  //  すべての設定可能なキーを取得する
  //
  //  @param
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  //  取得した文字列は呼び出し側でESDeleteJSON()を利用して削除すること
  //
  // {
  //    AllKeys : {
  //       "array_str" : [
  //          "< key name1 >" ,
  //          "< key name2 >" ,
  //       ]
  //    }
  // }
  //
  virtual ESErrorCode GetAllKeys(IESResultString* pstrResult) = 0;

  //
  //  指定したキーのデフォルト値を取得する
  //
  //  @param
  //   pszKey   : キー名
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  // {
  //    "< key name >" : 値データ ※別資料参照
  // }
  //
  virtual ESErrorCode GetDefaultValueForKey(ES_CHAR_CPTR pszKey,
                                            IESResultString* pstrResult) = 0;

  //
  //  指定したキーの設定値を取得する
  //
  //  @param
  //   pszKey   : キー名
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  // {
  //    "< key name >" : 値データ ※別資料参照
  // }
  //
  virtual ESErrorCode GetValueForKey(ES_CHAR_CPTR pszKey,
                                     IESResultString* pstrResult) = 0;

  //
  //  指定したキーに値を設定する
  //
  //  @param
  //   pszKey   : キー名
  //   ppszJSON : 設定値を記述したJSON文字列ポインタ
  //
  // {
  //    "< key name >" : 値データ ※別資料参照
  // }
  //
  virtual ESErrorCode SetValueForKey(ES_CHAR_CPTR pszKey,
                                     ES_JSON_CPTR pszJSON) = 0;

  //
  // JSONでまとめて値を設定する
  //
  // {
  //    "< key name1 >" : 値データ ※別資料参照
  //    "< key name2 >" : 値データ ※別資料参照
  //   ...
  // }
  //
  virtual ESErrorCode SetValuesWithJSON(ES_JSON_CPTR pszJSON) = 0;

  //
  //  指定したキーにセット可能なすべての値を取得する
  //
  //  param
  //   pszKey   : キー名
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  // {
  //    "< key name >" : 値データ ※別資料参照
  // }
  //
  virtual ESErrorCode GetAllValuesForKey(ES_CHAR_CPTR pszKey,
                                         IESResultString* pstrResult) = 0;

  //
  //  全キーに対する、セット可能なすべての値を取得する
  //
  //  param
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  // {
  //    "< key name1 >" : 値データ ※別資料参照 ,
  //    "< key name2 >" : 値データ ※別資料参照 ,
  //   ...
  // }
  //
  virtual ESErrorCode GetAllValues(IESResultString* pstrResult) = 0;

  //
  //  指定したキーにセット可能なすべての値を取得する
  //
  //  param
  //   pszKey   : キー名
  //   ppszJSON : 結果のJSON文字列を受け取るポインタ
  //
  // {
  //    "< key name >" : 値データ ※別資料参照
  // }
  //
  virtual ESErrorCode GetAvailableValuesForKey(ES_CHAR_CPTR pszKey,
                                               IESResultString* pstrResult) = 0;

  //
  //  全キーに対する、セット可能なすべての値を取得する
  //
  // {
  //    "< key name1 >" : 値データ ※別資料参照 ,
  //    "< key name2 >" : 値データ ※別資料参照 ,
  //   ...
  //   ...
  // }
  //
  virtual ESErrorCode GetAllAvailableValues(IESResultString* pstrResult) = 0;
};
