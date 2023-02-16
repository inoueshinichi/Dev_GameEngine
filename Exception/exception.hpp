/**
 * @file exception.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <framework.hpp>
#include <defs.hpp>
#include <format_string.hpp>
#include <transform_charactor.hpp>

#include <cstdio>  // std::snprintf
#include <cstdlib> // std::abort
#include <vector>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace is
{
    /**
     * @brief このマクロを通して例外をthrowする.
     * エラーコードは, common::error_codeのenum classで定義されている.
     * i.e : IS_ERROR(error_code::cuda_error, "Error size %d", size);
     */
#define IS_ERROR(code, msg, ...)                                                  \
    throw Exception(code, is::FormatString(msg, ##__VA_ARGS__),                   \
                    __func__, __FILE__, __LINE__);

    /**
     * @brief 特定の条件を満たすかどうかをチェックする.
     * エラーが発生したら，メッセージを投げる.
     * i.e : IS_CHECK(size == 2, error_code::cuda_error, "Error size %d", size);
     */
#define IS_CHECK(condition, code, msg, ...)                                            \
    if (!(condition)) {                                                                \
        IS_ERROR(code, std::string("Failed `" #condition "`: ") + msg, ##__VA_ARGS__)  \
    }

    /**
     * @brief 強制終了
     * 
     */
#define IS_FORCE_ASSERT(condition, msg, ...)                                         \
    if (!(condition)) {                                                              \
        std::cerr << "Aborting: " << is::FormatString(msg, ##__VA_ARGS__) << " at "  \
                  << __func__ << " in " << __FILE__ << ":" << __LINE__               \
                  << std::endl;                                                      \
        std::abort();                                                                \
    }


    /**
     * @brief Isにおけるエラーコード.
     * exception.cppの中にあるget_error_string()関数に
     * `CASE_ERROR_STRING({code name});`を追加しなればならない.
     */
    enum class ErrorCode {
        // 独自例外コード
        Unclassified = 0,
        NotImplemented,
        Value,
        Type,
        Memory,
        Io,
        Os,
        TargetSpecific,
        TargetSpecificAsync,
        Runtime
    };

    /**
     * @brief Get the error string object
     * 例外エラーを文字列で取得する関数
     * @param code 
     * @return string 
     */
    inline std::string GetErrorString(ErrorCode code)
    {
        switch (code)
        {
#define CASE_ERROR_STRING(code_name) \
case ErrorCode::code_name:           \
    return #code_name

            CASE_ERROR_STRING(Unclassified);
            CASE_ERROR_STRING(NotImplemented);
            CASE_ERROR_STRING(Value);
            CASE_ERROR_STRING(Type);
            CASE_ERROR_STRING(Memory);
            CASE_ERROR_STRING(Io);
            CASE_ERROR_STRING(Os);
            CASE_ERROR_STRING(TargetSpecific);
            CASE_ERROR_STRING(TargetSpecificAsync);
            CASE_ERROR_STRING(Runtime);
#undef CASE_ERROR_STRING
        }

        return std::string();
    }

    class IS_WIN_API Exception : public std::exception 
    {
    protected:
        ATL::CString mFullMsg;  // 表示されるFullメッセージ
        std::string mMsg;      // エラーメッセージ
        std::string mFunc;     // エラーが発生した関数名
        std::string mFile;     // エラーが発生したファイル名
        int mLine;        // エラーが発生した行番号

        ErrorCode mErrorCode;

    public:
        Exception(ErrorCode errorCode, const std::string &msg, const std::string &func, const std::string &file, int line)
            : mErrorCode(errorCode), mMsg(msg), mFunc(func), mFile(file), mLine(line)
        {
            std::ostringstream oss;
            oss << GetErrorString(errorCode) << " in "
                << mFunc << ":" << mLine << std::endl;
            oss << midiOutShortMsg << std::endl;
#if (defined(UNICODE) || defined(_UNICODE)) && !defined(_MBCS)
            mFullMsg = is::CvtShiftJisToUtf16(oss.str()).c_str();
#else
            mFullMsg = oss.str();
#endif
        }
        virtual ~Exception() noexcept {};
        virtual const TCHAR *What() const noexcept { return mFullMsg.GetString(); };
        is::ErrorCode GetError() const { return mErrorCode; }
    };
}