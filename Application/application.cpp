#include <application.hpp>
#include <event_dispatcher.hpp>

namespace is
{
    Application::Application(int argc, char** argv)
        : Object(nullptr)
        , mArgc(argc) 
        , mArgv(argv)
        , mEventDispatcher(nullptr)
    {
        Initialize();
    }

    Application::~Application()
    {
        Shutdown();
    }

    bool Application::Initialize()
    {
        handle::Instance& ins = Application::GetInstance();
        LPCTSTR name = Application::GetWindowClassName();
        handle::Icon& icon = Application::GetIcon();
        handle::SmallIcon& smallIcon = Application::GetSmallIcon();
        handle::Cursor& cursor = Application::GetCursor();
        handle::Brush& brush = Application::GetBackGround();
        handle::Accelerator& accel = Application::GetAccelerator();


        // Window Classの生成
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);                       // Window ClassEx Size
        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;      // Window Style
        wcex.cbClsExtra = 0;                                    // Window Class Extra
        wcex.cbWndExtra = 0;// DLGWINDOWEXTRA;                  // Window Handle Extra
        wcex.hInstance = ins.hInstance;                           // Window Instance
        wcex.hIcon = icon.hIcon;                                  // Window Icon                
        wcex.hCursor = cursor.hCursor;                            // Window Cursor                                
        wcex.hbrBackground = brush.hBrush;                        // Window Background
        wcex.lpszMenuName = NULL;                                 // Window Menu       // = MAKEINTRESOURCEW(IDC_WINCVAPP_MENU); 
        wcex.lpszClassName = name;                                // Window Class Name
        wcex.hIconSm = smallIcon.hSmallIcon;                      // Window Small Icon      
        wcex.lpfnWndProc = EventDispatcher::ThreadSharedProcedure;// Window Procedure


        // WindowsMessageシステムを生成
        mEventDispatcher = new EventDispatcher();

        return true;
    }

    void Application::Shutdown()
    {
        if (mEventDispatcher)
        {
            delete mEventDispatcher;
        }
    }

    int Application::Exe()
    {
        return RunLoop();
    }

    int Application::RunLoop()
    {
        MSG msg; // Windows Message

        // メッセージループ
        while (true)
        {
            // カレントスレッドのWinMsgQueueにメッセージが来てるか覗く
            if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) > 0)
            {
                // メッセージを取得
                if (GetMessage(&msg, NULL, 0, 0) > 0)
                {

                }
                else
                {
                    // WM_QUIT or エラー
                    break;
                }
            }
        }
        return true;
    }

    handle::Instance &Application::GetInstance()
    {
        static handle::Instance ins;
        ins.hInstance = ::GetModuleHandle(NULL);
        
        /*Win32APIエラーのチェック*/
        if (!ins.hInstance)
        {
            IS_WIN_API_ERROR(::GetLastError(), "hInstance")
        }
        return ins;
    }

    LPCTSTR Application::GetWindowClassName()
    {
        // https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-wndclassexa
        static constexpr int LENGTH_WCN = 256;
        static TCHAR mWindowClassName[LENGTH_WCN];
        IS_ZERO_MEMORY(mWindowClassName, sizeof(TCHAR) * LENGTH_WCN)
        _tcscpy(mWindowClassName, _T("MyWindowClass"));
        return mWindowClassName;
    }

    handle::Icon &Application::GetIcon()
    {
        static handle::Icon icon;
        icon.hIcon = LoadIcon(
            Application::GetInstance().hInstance, 
		    MAKEINTRESOURCE(IDI_WINNATIVEGUIWITHXAML));

        /*Win32APIエラーのチェック*/
        if (!icon.hIcon)
        {
            IS_WIN_API_ERROR(::GetLastError(), "hIcon")
        }
        return icon;
    }

    handle::SmallIcon &Application::GetSmallIcon()
    {
        static handle::SmallIcon smallIcon;
        smallIcon.hSmallIcon =  LoadIcon(
            Application::GetInstance().hInstance, 
		    MAKEINTRESOURCE(IDI_SMALL));

        /*Win32APIエラーのチェック*/
        if (!smallIcon.hSmallIcon)
        {
            IS_WIN_API_ERROR(::GetLastError(), "hSmallIcon")
        }
        return smallIcon;
    }

    handle::Cursor &Application::GetCursor()
    {
        static handle::Cursor cursor;
        cursor.hCursor = LoadCursor(nullptr, IDC_ARROW);

        /*Win32APIエラーのチェック*/
        if (!cursor.hCursor)
        {
            IS_WIN_API_ERROR(::GetLastError(), "hCursor")
        }
        return cursor;
    }

    handle::Brush &Application::GetBackGround()
    {
        static handle::Brush brush;
        brush.hBrush = (HBRUSH)(COLOR_WINDOW + 1);
        return brush;
    }

    handle::Accelerator &Application::GetAccelerator()
    {
        static handle::Accelerator accel;
        accel.hAccel = LoadAccelerators(
            Application::GetInstance().hInstance, 
            MAKEINTRESOURCE(IDC_WINNATIVEGUIWITHXAML));

        /*Win32APIエラーのチェック*/
        if (!accel.hAccel)
        {
            IS_WIN_API_ERROR(::GetLastError(), "hAccel")
        }
        return accel;
    }
}