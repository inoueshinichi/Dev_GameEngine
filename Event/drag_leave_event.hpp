/**
 * @file drag_leave_event.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <pch.hpp>
#include <drag_event.hpp>

namespace is
{
    class IS_WIN_API DragLeaveEvent : public DragEvent
    {
    public:
        virtual ~DragLeaveEvent() {}
        virtual const TCHAR *GetClassName() const override { return _T("DragLeaveEvent"); }
    };
}