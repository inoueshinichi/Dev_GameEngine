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
#include <atlstr.h>    // CString
#include <atldef.h>    // AtlThrow, AtlThrowLastWin32 https://learn.microsoft.com/ja-jp/cpp/atl/reference/debugging-and-error-reporting-global-functions?view=msvc-170
#include <atlcomcli.h> // AtlHresultFromLastError, AtlHresultFromWin32
#include <atlcom.h>    // AtlReportError

/*WinRT*/
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>

// 名称かぶり対策-1
#pragma push_macro("GetCurrentTime")
#pragma push_macro("TRY")
#undef GetCurrentTime
#undef TRY
// 名称かぶり対策-1

#include <winrt/Windows.UI.Xaml.Hosting.h>             // WindowsXamlManager
#include <winrt/Windows.UI.Xaml.Markup.h>              // XamlReader
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h> // Click
#include <winrt/Windows.UI.Xaml.Media.h>               // SolidColorBrush
#include <winrt/Windows.Foundation.h>                  // IAsyncAction
#include <winrt/Windows.Security.Cryptography.h>       // CryptographicBuffer

// 名称かぶり対策-2
#pragma push_macro("GetCurrentTime")
#pragma push_macro("TRY")
#undef GetCurrentTime
#undef TRY
// 名称かぶり対策-2


#include "resource.h"

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::Foundation;
using namespace Windows::Security::Cryptography;





