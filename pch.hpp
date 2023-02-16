/**
 * @file pch.hpp
 * @author your name (you@domain.com)
 * @brief コンパイル済みヘッダー
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <framework.hpp>
#include <defs.hpp>
#include <transform_charactor.hpp>
#include <windows_handler.hpp>
#include <win_api_exception.hpp>
#include <com_hr_exception.hpp>

namespace is
{
    // 名前からXamlコントロールを特定するテンプレート
    template <typename T>
    T Element(const WCHAR *name)
    {
        return _xamlroot.Content().as<Panel>().FindName(name).as<T>();
    }
}