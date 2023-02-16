/**
 * @file framework.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN // Windows ヘッダーから使用されていない部分を除外します。
#endif

#include <targetver.hpp>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS // 一部の CString コンストラクターは明示的です。

/*Windows*/
#define NOMINMAX
#include <Windows.h>
#include <WinUser.h>
#include <CommCtrl.h>
#include <tchar.h> // TChar

/*ATL*/
#include <atlbase.h>
#include <atlstr.h> // CString

// https://learn.microsoft.com/ja-jp/cpp/atl/reference/debugging-and-error-reporting-global-functions?view=msvc-170
#include <atldef.h>    // AtlThrow, AtlThrowLastWin32
#include <atlcomcli.h> // AtlHresultFromLastError, AtlHresultFromWin32
#include <atlcom.h>    // AtlReportError


