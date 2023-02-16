/**
 * @file focus_event.hpp
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
#include <event.hpp>

namespace is
{
    class IS_WIN_API FocusEvent : public Event
    {
    public:
        virtual ~FocusEvent() {}
        virtual const TCHAR *GetClassName() const override final { return _T("FocusEvent"); }
    };
}

