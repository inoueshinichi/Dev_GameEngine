/**
 * @file widget.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <pch.hpp>
#include <object.hpp>

namespace is
{
    class IS_WIN_API Widget : public Object
    {
        enum class State
        {
            EActive = 0,
            EPending,
            EDead,
        };
    public:
        Widget(Widget *parent = nullptr) : Object(parent), mState(Widget::State::EActive) {}
        virtual ~Widget() {}
        virtual const TCHAR *GetClassName() const override { return _T("Widget"); }

    private:
        State mState;

        IS_DISABLE_COPY_AND_ASSIGN(Widget)
    };
}