/**
 * @file application.hpp
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
    class IS_WIN_API Application : public Object
    {
    public:
        Application(int argc, char **argv);
        virtual ~Application();
        const TCHAR *GetClassName() const override final { return _T("Application"); }

        int Exe();

        static handle::Instance &GetInstance();
        static LPCTSTR GetWindowClassName();
        static handle::Icon &GetIcon();
        static handle::SmallIcon &GetSmallIcon();
        static handle::Cursor &GetCursor();
        static handle::Brush &GetBackGround();
        static handle::Accelerator &GetAccelerator();

    protected:
        virtual bool Initialize();
        virtual void Shutdown();
        virtual int RunLoop();

    private:
        int mArgc;
        char **mArgv;
        class EventDispatcher *mEventDispatcher;
    };
}
