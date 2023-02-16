/**
 * @file com_hr_exception.hpp
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

/**
 * @brief HRESULTに関して
 * https://learn.microsoft.com/ja-jp/cpp/windows/attributes/attribute-programming-faq?view=msvc-170
 *
 * HRESULT は単純なデータ型. 一般的にWidows-ATLによって戻り値としてよく使用される.
 * Windows API エラーから主なエラーコードを抜粋してCOM仕様に仕立ててある.
 */

namespace is
{
    /* Windows-COMに関する例外スロー */
#define IS_COM_HR_ERROR(hr, msg, ...)                                      \
    throw ComHrException(hr, is::common::FormatString(msg, ##__VA_ARGS__), \
                    __func__, __FILE__, __LINE__);

#define IS_COM_HR_CHECK(hr, msg, ...)                                               \
    if (FAILED(hr))                                                                 \
    {                                                                               \
        IS_COM_HR_ERROR(hr, std::string("Failed `" #hr "`: ") + msg, ##__VA_ARGS__) \
    }

#define IS_COM_HR_FORCE_ASSERT(hr, msg, ...)                                      \
    if (FAILED(hr))                                                               \
    {                                                                             \
        std::cerr << "Aborting: " << is::common::FormatString(msg, ##__VA_ARGS__) \
                  << " at " << __func__                                           \
                  << " in " << __FILE__                                           \
                  << ":" << __LINE__                                              \
                  << std::endl;                                                   \
        std::abort();                                                             \
    }

    inline ATL::CString GetComHrErrorString(HRESULT hr)
    {
        /* ShiftJisでメッセージ作成 */
        int size = std::snprintf(nullptr, 0, "HRESULT of 0x%08X", static_cast<UINT>(hr));
        if (size < 0)
        {
            _tprintf(_T("Fatal error: std::snprintf() in GetAtlHrErrorString.\n"));
            std::abort();
        }

        /* バッファサイズを算出(文字列長 + null文字サイズ) */
        size_t bufSize = size + sizeof(char);

        /* バッファサイズ分メモリ確保 */
        std::vector<char> buf(bufSize);

        /* 文字列のフォーマット */
        std::snprintf(buf.data(), buf_size, "HRESULT of 0x%08X", static_cast<UINT>(hr));

        /* ShiftJisメッセージ */
        std::string msg(buf.data(), buf.data() + size);
        ATL::CString retMsg;

#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_MBCS)
        // ShiftJis -> UTF-16
        std::wstring tmpMsg = CvtShiftJisToUtf16(msg);
        retMsg = tmpMsg.c_str();
#else
        // through ShiftJis
        retMsg = msg.c_str();
#endif
        return retMsg;
    }

    /**
     * @brief Com HRESULT HANDLE Exception クラス
     *
     */
    class IS_WIN_API ComHrException : public std::exception
    {
    protected:
        ATL::CString mFullMsg; // 表示されるFullメッセージ
        ATL::CString mMsg;     // エラーメッセージ
        ATL::CString mFunc;    // エラーが発生した関数名
        ATL::CString mFile;    // エラーが発生したファイル名
        int mLine;             // エラーが発生した行番号

        HRESULT mResult; // WindowsのHRESULTハンドル
    public:
        ComHrException(HRESULT hr, const std::string &msg, const std::string &func, const std::string &file, int line)
            : mResult(hr), mMsg(msg.c_str()), mFunc(func.c_str()), mFile(file.c_str()), mLine(line)
        {
#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_MBCS)
            std::wostringstream woss;
            woss << GetComHrErrorString(mResult).GetString() << L" in "
                    << mFunc.GetString() << L":" << mLine << std::endl;
            woss << mMsg.GetString() << std::endl;
            mFullMsg = woss.str().c_str();
#else
            std::ostringstream oss;
            oss << GetComHrErrorString(mResult).GetString() << " in "
                << mFunc.GetString() << ":" << mLine << std::endl;
            oss << mMsg.GetString() << std::endl;
            mFullMsg = oss.str().c_str();
#endif
        }

        virtual ~ComHrException() noexcept {}
        virtual LPTCSTR What() const noexcept { return mFullMsg.GetString(); }
        HRESULT GetHrError() const { return mResult; }
    };
}