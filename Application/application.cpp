#include <application.hpp>

namespace is
{
    IS_ZERO_MEMORY(Application::mWindowClassName, sizeof(TCHAR) * Application::LENGTH_WCN)

    Application::Application(int argc, char** argv)
        : Object(nullptr)
        , mArgc(argc) 
        , mArgv(argv)
    {
        Initialize();
    }

    Application::~Application()
    {
        Shutdown();
    }

    bool Application::Initialize()
    {

    }

    void Application::Shutdown()
    {

    }

    int Application::Exe()
    {
        return Run();
    }

    int Application::RunLoop()
    {

    }

    Instance &Application::GetInstance()
    {
        static Instance ins;
        ins.hInstance = ::GetModuleHandle(NULL);
        
        /*Win32APIエラーのチェック*/

        return ins;
    }
}