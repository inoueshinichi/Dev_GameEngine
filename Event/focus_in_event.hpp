/**
 * @file focus_in_event.hpp
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
#include <focus_event.hpp>

namespace is
{
    class IS_WIN_API FocusInEvent : public FocusEvent
    {
    public:
        ~FocusInEvent() {}
        const TCHAR *GetClassName() const override final { return _T("FocusInEvent"); }
    };
}