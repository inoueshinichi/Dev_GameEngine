/**
 * @file rtti.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

/////////////////////////////
// C++クラス名のデマングル
/////////////////////////////
#include <typeinfo>
#include <iostream>

#if defined(_MSC_VER)
    #if !defined(_DEBUG) || defined(NDEBUG)
        #define IS_SINGLETON_LOG(message, singleton)
    #else
        #define IS_SINGLETON_LOG(message singleton)               \
            std::cout << "[" << #message << "]: a singleton `" << \
            typeid(singleton).name() << "`" << std::endl;
    #endif
#else
    #if defined(NDEBUG)
        #define IS_SINGLETON_LOG(message, singleton)
    #else
        // UNIX系だとlibstdc++に含まれる.
        // Windowsはvcruntime14X.dllかな...
        #if __has_include(<cxxabi.h>)
            #include <cxxabi.h>
            #define IS_SINGLETON_LOG(message, singleton)                                                     \
            std::string singleton_name;                                                                      \
            const std::type_info &type_id = typeid(singleton); /* RTTI */                                    \
            int stat{-1};                                                                                    \
            char *name = abi::__cxa_demangle(type_id.name(), 0, 0, &stat);                                   \
            if (name != nullptr)                                                                             \
            {                                                                                                \
                if (stat == 0) /* success: stat == 0 */                                                      \
                {                                                                                            \
                    singleton_name = name;                                                                   \
                    std::cout << "[" << #message << "] a singleton `" << singleton_name << "`" << std::endl; \
                    ::free(name);                                                                            \
                }                                                                                            \
            }                                                                                                \
            if (stat != 0)                                                                                   \
            {                                                                                                \
                std::cout << "[" << #message << "] a singleton `" <<                                         \
                    typeid(SINGLETON).name() << "`" << std::endl;                                            \
            }
        #else
            #define IS_SINGLETON_LOG(message, singleton)               \
                std::cout << "[" << #message << "]: a singleton `" << \
                typeid(singleton).name() << "`" << std::endl;
        #endif
    #endif
#endif