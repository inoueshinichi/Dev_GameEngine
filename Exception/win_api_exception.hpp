/**
 * @file win_api_exception.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <framework.hpp>
#include <defs.hpp>
#include <format_string.hpp>

#include <cstdio>  // std::snprintf
#include <cstdlib> // std::abort
#include <vector>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace is
{
    /* Windows-APIに関する例外スロー */
#define IS_WIN_API_ERROR(winErrorCode, msg, ...)                                      \
    throw WinApiException(winErrorCode, is::FormatString(msg, ##__VA_ARGS__), \
                          __func__, __FILE__, __LINE__);

#define IS_WIN_API_CHECK(winErrorCode, msg, ...)                                                        \
    if (winErrorCode != NO_ERROR)                                                                       \
    {                                                                                                   \
        IS_COM_HR_ERROR(winErrorCode, std::string("Failed `" #winErrorCode "`: ") + msg, ##__VA_ARGS__) \
    }

#define IS_WIN_API_FORCE_ASSERT(winErrorCode, msg, ...)                           \
    if (winErrorCode != NO_ERROR)                                                 \
    {                                                                             \
        std::cerr << "Aborting: " << is::FormatString(msg, ##__VA_ARGS__)         \
                  << " at " << __func__                                           \
                  << " in " << __FILE__                                           \
                  << ":" << __LINE__                                              \
                  << std::endl;                                                   \
        std::abort();                                                             \
    }

    /**
     * @brief Win32API Error を取得する
     * http://yamatyuu.net/computer/program/sdk/base/errmsg1/index.html
     * @return CString
     * errorCode returned from ::GetLastError()
     */
    inline CString GetWinApiErrorString(DWORD errorCode)
    {
        LPVOID lpMsgBuf;
        DWORD dwChars; // Number of chars returns;

        /**
         * DWORD FormatMessage(
         *  DWORD dwFlags,      // 入力元と処理方法のオプション
         *  LPCVOID lpSource,   // メッセージの入力元
         *  DWORD dwMessageId,  // メッセージ識別子
         *  DWORD dwLanguageId, // 言語識別子
         *  LPTSTR lpBuffer,    // メッセージバッファ
         *  DOWRD nSize,        // メッセージバッファの最大サイズ
         *  va_list* Arguments  // 複数のメッセージ挿入シーケンスからなる配列
         * )
         */
        dwChars = ::FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |   // テキストのメモリ割り当てを要求
            FORMAT_MESSAGE_FROM_SYSTEM |       // エラーメッセージはWindowsが用意しているものを使用
            FORMAT_MESSAGE_IGNORE_INSERTS,     // 次の引数を無視してエラーコードに対するエラーメッセージを作成する
            NULL,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 言語(日本語)を設定
            (LPTSTR)&lpMsgBuf,                         // メッセージテキストが保存されるバッファへのポインタ
            0,
            NULL);

        if (dwChars == 0)
        {
            // The error code did not exist in the system errors.
            // Try Ntdsbmsg.dll for the error code.
            HINSTANCE hInstance;

            // Load the library.
            hInstance = LoadLibrary(_T("Ntdsbmsg.dll"));
            if (hInstance == NULL)
            {
                _tprintf(_T("Can not load Ntdsbmsg.dll\n"));
                std::abort();
            }

            dwChars = ::FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                errorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 言語(日本語)を設定
                (LPTSTR)&lpMsgBuf,
                0,
                NULL);
        }

        // コピー
        CString errorMsg((LPTSTR)&lpMsgBuf);

        // ヒープメモリ解放
        LocalFree(lpMsgBuf);

        return errorMsg;
    }

    class IS_WIN_API WinApiException : public std::exception
    {
    protected:
        ATL::CString mFullMsg; // 表示されるFullメッセージ
        std::string mMsg;      // エラーメッセージ
        std::string mFunc;     // エラーが発生した関数名
        std::string mFile;     // エラーが発生したファイル名
        int mLine;             // エラーが発生した行番号

        DWORD mWinApiErrorCode;

    public:
        WinApiException(DWORD winApiErrorCode, const std::string &msg, const std::string &func, const std::string &file, int line)
            : mWinApiErrorCode(winApiErrorCode), mMsg(msg), mFunc(func), mFile(file), mLine(line)
        {
#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_MBCS)
            std::wostringstream woss;
            woss << GetWinApiErrorString(mWinApiErrorCode).GetString() << L" in "
                 << is::CvtShiftJisToUtf16(mFunc) << L":" << mLine << std::endl;
            woss << is::CvtShiftJisToUtf16(mMsg) << std::endl;
            mFullMsg = woss.str().c_str();
#else
            std::ostringstream oss;
            oss << GetWinApiErrorString(mWinApiErrorCode).GetString() << " in "
                << mFunc << ":" << mLine << std::endl;
            oss << mMsg << std::endl;
            mFullMsg = oss.str().c_str();
#endif
        }

        virtual ~WinApiException() noexcept {}
        virtual const TCHAR *What() const noexcept { return mFullMsg.GetString(); }
        DWORD GetWinError() const { return mWinApiErrorCode; }
    };
}