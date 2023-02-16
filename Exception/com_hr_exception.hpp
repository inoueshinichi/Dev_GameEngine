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
#define IS_COM_HR_ERROR(hr, msg, ...)                              \
    throw ComHrException(hr, is::FormatString(msg, ##__VA_ARGS__), \
                    __func__, __FILE__, __LINE__);

#define IS_COM_HR_CHECK(hr, msg, ...)                                               \
    if (FAILED(hr))                                                                 \
    {                                                                               \
        IS_COM_HR_ERROR(hr, std::string("Failed `" #hr "`: ") + msg, ##__VA_ARGS__) \
    }

#define IS_COM_HR_FORCE_ASSERT(hr, msg, ...)                                      \
    if (FAILED(hr))                                                               \
    {                                                                             \
        std::cerr << "Aborting: " << is::FormatString(msg, ##__VA_ARGS__)         \
                  << " at " << __func__                                           \
                  << " in " << __FILE__                                           \
                  << ":" << __LINE__                                              \
                  << std::endl;                                                   \
        std::abort();                                                             \
    }

    inline std::string GetComHrErrorString(HRESULT hr)
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
        std::snprintf(buf.data(), bufSize, "HRESULT of 0x%08X", static_cast<UINT>(hr));

        /* ShiftJisメッセージ */
        std::string msg(buf.data(), buf.data() + size);
        return msg;
    }

    /**
     * @brief Com HRESULT HANDLE Exception クラス
     *
     */
    class IS_WIN_API ComHrException : public std::exception
    {
    protected:
        ATL::CString mFullMsg; // 表示されるFullメッセージ
        std::string  mMsg;     // エラーメッセージ
        std::string  mFunc;    // エラーが発生した関数名
        std::string  mFile;    // エラーが発生したファイル名
        int mLine;             // エラーが発生した行番号

        HRESULT mHr; // WindowsのHRESULTハンドル
    public:
        ComHrException(HRESULT hr, const std::string &msg, const std::string &func, const std::string &file, int line)
            : mHr(hr), mMsg(msg), mFunc(func), mFile(file), mLine(line)
        {
            std::ostringstream oss;
            oss << GetComHrErrorString(mHr) << " in "
                << mFunc << ":" << mLine << std::endl;
            oss << mMsg << std::endl;

#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_MBCS)
             mFullMsg =  is::CvtShiftJisToUtf16(oss.str()).c_str();
#else
             mFullMsg = oss.str().c_str();
#endif
        }

        virtual ~ComHrException() noexcept {}
        virtual const TCHAR * What() const noexcept { return mFullMsg.GetString(); }
        HRESULT GetHrError() const { return mHr; }
    };
}