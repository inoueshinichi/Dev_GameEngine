/**
 * @file window.hpp
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

namespace is
{
    namespace handle
    {
        struct IS_WIN_API Window
        {
            HWND hWnd;
        };
    }
}