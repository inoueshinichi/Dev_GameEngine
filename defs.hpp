/**
 * @file defs.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#if defined(_MSC_VER)
    // __func__の定義
    #define __func__ __FUNCTION__
#endif

#if defined(_MSC_VER)
    // 「exportされたクラス」が「privateなメンバ変数を持つexportされていないクラス」を使う時に出る
    // https://qiita.com/Chironian/items/462a3bdf271d5f0b00b6#%EF%BC%92%EF%BC%93c4251%E8%AD%A6%E5%91%8A%E3%81%8C%E5%87%BA%E3%82%8B
    #pragma warning(disable : 4251)
#endif

// DLL Exports
#if defined(_MSC_VER)
    #if defined(IsWin_EXPORTS) || defined(IsWin_dbg_EXPORTS)
        #define IS_WIN_API __declspec(dllexport)
    #else
        #define IS_WIN_API __declspec(dllimport)
    #endif
#else
    #define IS_WIN_API
#endif

// 呼び出し規則
#if defined(_MSC_VER)
    #define IS_ATTR_CALL
#else
    #define IS_ATTR_CALL
#endif

// プリプロセッサによるマクロ内可変長マクロの展開補助
#if defined(_MSC_VER) && _MSC_VER < 1925 // >= Visual Studio 2019 16.5.1
    // _MSVC_TRADITIONAL 従来:1, 準拠:0
    #if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL // 従来型プリプロセッサ
        // マクロ内の可変長マクロの展開を補助するマクロを定義
        #define IS_MACRO_VA_EXPAND(...) __VA_ARGS__
    #endif
#endif

// コピーコンストラクタとコピー代入演算子の外部公開を禁止する
#define IS_DISABLE_COPY_AND_ASSIGN(class_name) \
private:                                       \
    class_name(const class_name &) = delete;   \
    class_name &operator=(const class_name &) = delete;

// 文字列の取得
#define IS_STR(name) #name


#if defined(_MSC_VER)
    #include <clocale>
    #define IS_DEFINE_SHIFTJIS_TO_UTF8 std::local::global(std::local(""));
#else
    #define IS_DEFINE_SHIFTJIS_TO_UTF8
#endif

// C++11 gives alignas as standard
// http://en.cppreference.com/w/cpp/language/alignas
#define IS_ALIGN(N) alignas(N)


//////////////////////////////////
// C++ version毎の差異を吸収するマクロ
//////////////////////////////////
#if (__cplusplus < 201704L)
    #define IS_INVOKE_RESULT_TYPE(Func, Args) typename std::result_of<Func(Args...)>::type
#else
    #define IS_INVOKE_RESULT_TYPE(Func, Args) typename std::invoke_result<Func, Args...>::type
#endif

// Memory
#include <cstring>
#define IS_ZERO_MEMORY(ptr, bytesize) std::memset((void *)ptr, 0, bytesize);


/////////////////////////////////
// プリミティブ型のエイリアス
/////////////////////////////////
using uchar = unsigned char;
using byte = char;
using ubyte = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using longlong = long long;
using ulonglong = unsigned long long;

using int16 = short;
using uint16 = unsigned short;


#if defined(_WIN64) && defined(_WIN32) // 32bit環境
    using int32 = long;
    using uint32 = unsigned long;
    using int64 =  long long;
    using uint64 = unsigned long long;
#else
    #if defined(__linux__) // Linux
        using int32 = int;
        using uint32 = unsigned int;
        using int64 = long long;
        using uint64 = unsigned long long;
    #elif defined(__MACH__)  // macOS
        using int32 = int;
        using uint32 = unsigned int;
        using int64 = long long;
        using uint64 = unsigned long long;
    #else
        using int32 = int;
        using uint32 = unsigned int;
        using int64 = long long;
        using uint64 = unsigned long long;
    #endif
#endif

using longdouble = long double;