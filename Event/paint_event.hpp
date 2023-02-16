/**
 * @file paint_event.hpp
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
    class IS_WIN_API PaintEvent : public Event
    {
    public:
        virtual ~PaintEvent() {}
        virtual const TCHAR *GetClassName() const override final { return _T("PaintEvent"); }
    };
}