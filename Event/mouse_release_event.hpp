/**
 * @file mouse_release_event.hpp
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
#include <mouse_event.hpp>

namespace is
{
    class IS_WIN_API MouseReleaseEvent : public MouseEvent
    {
    public:
        virtual ~MouseReleaseEvent() {}
        virtual const TCHAR *GetClassName() const override final { return _T("MouseReleaseEvent"); }
    };
}