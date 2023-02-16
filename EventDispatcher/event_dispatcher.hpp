/**
 * @file event_dispatcher.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <pch.hpp>
#include <singleton_manager.hpp>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>

namespace is
{
    using GlobalWidgetMap = std::unordered_map<HWND, std::pair<class Widget*, int>>;
    using GlobalDispatcherMap = std::vector<std::pair<class EventDispatcher*, DWORD>>;

    /*各スレッドに一つのインスタンスのみ*/
    class IS_WIN_API EventDispatcher
    {
    public:
        virtual ~EventDispatcher() {}
        virtual const TCHAR *GetClassName() const { return _T("EventDispatcher"); }
        std::thread::id GetCurrentThreadId() const;

        // 最初にシステムからメッセージが届くウィンドウプロシージャ(関数記述は同じだが, 各スレッドで異なるインスタンスで処理が走る)
        static LRESULT CALLBACK ThreadSharedProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // 各スレッドから呼ばれるので排他的処理が必須

        EventDispatcher();
        ~EventDispatcher();
    private:
        static std::mutex &GetMutex();
       
        static void AddRef(HWND hWnd);
        static void SubRef(HWND hWnd);

        static GlobalWidgetMap &GetGlobalWidgetMap();
        static void RegisterWidget(HWND hWnd, class Widget* widget);
        static void UnreigsterWidget(HWND hWnd);

        static GlobalDispatcherMap &GetGlobalDispatcherMap();
        static void RegisterDispatcher(EventDispatcher* dispatcher, DWORD threadId);
        static void UnregisterDispatcher(EventDispatcher* dispatcher);

        static class Widget* GetWidgetPointer(HWND hWnd);

        IS_DISABLE_COPY_AND_ASSIGN(EventDispatcher)
    };
}