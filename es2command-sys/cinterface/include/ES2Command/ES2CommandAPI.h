// This file is copied from epsonscan2 6.7.43.0-1
// The original file is licensed as LGPL 2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//! @file     ES2CommandAPI.h
//!
//! @brif     スキャナー操作インターフェースの定義
//!           DLL アプリケーション用にエクスポートされる関数を定義します。
//! @note
//! @versoin  1.0
//! @par      Copyright SEIKO EPSON Corporation
//! @par      更新履歴
//! @par        - 新規作成       2014/12/25
//!
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////
//
// DLL設定の定義
//
///////////////////////////////////////////////////////////////////
#define _UNICODE_ESSCANNER  // Unicode版

#if defined(ES2COMMAND_EXPORTS)
#define ESSCANNER_API __declspec(dllexport)
#elif defined(ES2COMMAND_EXPORTS)
#define ESSCANNER_API __declspec(dllimport)
#else
#define ESSCANNER_API
#endif

#include "ESCommandProperties.h"
#include "IESScanner.h"

extern "C" {

// [ ESCreateScanner ]
//
//  スキャナ操作インターフェースの作成
//
//  @param
//   eCommandType : スキャナのコマンドタイプ
//   ppScanner    :
//   作成されたスキャナーインターフェースを受け取るポインタへのポインタ
//  @return
//   エラーコード
//   成功 : kESErrorNoError
//   失敗 : その他
ESSCANNER_API ESErrorCode ESCreateScanner(ESCommandType eCommandType,
                                          IESScanner** ppScanner);
};

typedef ESErrorCode (*PFN_CREATE_SCANNER)(ESCommandType eCommandType,
                                          IESScanner** ppScanner);
