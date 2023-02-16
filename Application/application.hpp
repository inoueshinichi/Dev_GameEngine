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
        Application(int argc, char** argv);
        virtual ~Application();
        const TCHAR *GetClassName() const override final { return _T("Application"); }

        int Exe();

        static Instance &GetInstance();
        static LPTCSTR GetWindowClassName();
        static Icon &GetIcon();
        static SmallIcon &GetSmallIcon();
        static Cursor &GetCursor();
        static Brush &GetBackGround();
        static Accelerator &GetAccelerator();


    protected:
        virtual bool Initialize();
        virtual void Shutdown();
        virtual int RunLoop();

    private:
        int mArgc;
        char** mArgv;

        // https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-wndclassexa
        constexpr int LENGTH_WCN = 256;
        static TCHAR mWindowClassName[LENGTH_WCN];
    };
}
