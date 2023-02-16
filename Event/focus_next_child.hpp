/**
 * @file focus_next_child.hpp
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
    class IS_WIN_API FocusNextChildEvent : public FocusEvent
    {
    public:
        ~FocusNextChildEvent() {}
        const TCHAR *GetClassName() const override final { return _T("FocusNextChildEvent"); }
    };
}