/**
 * @file event.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <pch.hpp>
#include <object.hpp>

namespace is
{
    class IS_WIN_API Event : public Object
    {
    public:
        virtual ~Event() {}
        virtual const TCHAR* GetClassName() const override { return _T("Event"); }
    };
}