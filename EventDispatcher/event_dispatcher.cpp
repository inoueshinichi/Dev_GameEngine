#include <event_dispatcher.hpp>
#include <widget.hpp>


namespace is
{
    EventDispatcher::EventDispatcher()
    {
        RegisterDispatcher(this, ::GetCurrentThreadId());

        // PeekMessageでカレントスレッドにWindows Message Queueを生成 
        MSG msg;
        PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE); 
    }

    EventDispatcher::~EventDispatcher()
    {
        UnregisterDispatcher(this);
    }

    // private static
    GlobalDispatcherMap &EventDispatcher::GetGlobalDispatcherMap()
    {
        static GlobalDispatcherMap registryDispather;
        return registryDispather;
    }

    // private static
    void EventDispatcher::RegisterDispatcher(EventDispatcher* dispatcher, DWORD threadId)
    {
        GlobalDispatcherMap &registryDispather = GetGlobalDispatcherMap();
        auto iter = std::find_if(registryDispather.begin(), registryDispather.end(),
                                 [&dispatcher](auto& pair) { if (pair.first == dispatcher) { return true; }});
        if (iter == registryDispather.end())
        {
            registryDispather.emplace_back(dispatcher, threadId);
        }
        else
        {
            // 同じスレッドに2つ目のEventDispatcherを生成しようとしてエラー
            IS_ERROR(ErrorCode::TargetSpecific, "一つのスレッドにEventDispatcherは1つしか生成できません. Thread ID: %ld", ::GetCurrentThreadId());
        }
    }

    // private static
    void EventDispatcher::UnregisterDispatcher(EventDispatcher* dispatcher)
    {
        GlobalDispatcherMap &registryDispather = GetGlobalDispatcherMap();
        auto iter = std::find_if(registryDispather.begin(), registryDispather.end(),
                                 [&dispatcher](auto& pair) { if (pair.first == dispatcher) { return true; }});
        if (iter != registryDispather.end())
        {
            std::iter_swap(iter, registryDispather.end() - 1);
            registryDispather.pop_back();
        }
    }

    // private static
    std::mutex &EventDispatcher::GetMutex()
    {
        // 内部リンケージ
        static std::mutex sMtx;
        return sMtx;
    }

    // private static
    GlobalWidgetMap &EventDispatcher::GetGlobalWidgetMap()
    {
        static GlobalWidgetMap registryWidget;
        return registryWidget;
    }

    // private static
    void EventDispatcher::RegisterWidget(HWND hWnd, Widget* widget)
    {
        GlobalWidgetMap& registryWidget = EventDispatcher::GetGlobalWidgetMap();
        auto iter = registryWidget.find(hWnd);
        if (iter == registryWidget.end())
        {
            registryWidget.emplace(hWnd, std::make_pair(widget, (int)0));
        }
    }

    // private static
    void EventDispatcher::UnreigsterWidget(HWND hWnd)
    {
        GlobalWidgetMap& registryWidget = EventDispatcher::GetGlobalWidgetMap();
        auto iter = registryWidget.find(hWnd);
        if (iter != registryWidget.end())
        {
            if ((*iter).second.second <= 0)
            {
                registryWidget.erase(hWnd);
            }
        }
    }

    // private static
    void EventDispatcher::AddRef(HWND hWnd)
    {
        GlobalWidgetMap& registryWidget = EventDispatcher::GetGlobalWidgetMap();
        auto iter = registryWidget.find(hWnd);
        if (iter != registryWidget.end())
        {
            std::mutex &sMtx = GetMutex();
            std::lock_guard<std::mutex> locker(sMtx);
            (*iter).second.second += 1;
        }
        
    }

    // private static
    void EventDispatcher::SubRef(HWND hWnd)
    {
        GlobalWidgetMap& registryWidget = EventDispatcher::GetGlobalWidgetMap();
        auto iter = registryWidget.find(hWnd);
        if (iter != registryWidget.end())
        {
            std::mutex &sMtx = GetMutex();
            std::lock_guard<std::mutex> locker(sMtx);
            (*iter).second.second -= 1;
        }
    }

     // private static
    Widget* EventDispatcher::GetWidgetPointer(HWND hWnd)
    {
        GlobalWidgetMap& registryWidget = EventDispatcher::GetGlobalWidgetMap();
        return registryWidget[hWnd].first;
    }


    ///////////////////////////////////////////////////////////////////////////
    // ************************** Window Messages ************************** //
    ///////////////////////////////////////////////////////////////////////////
    // public static @Note イベントループが存在する各スレッドから呼ばれる
    LRESULT EventDispatcher::ThreadSharedProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        std::thread::id currentThreadId;
        Widget* widget = nullptr;
        LRESULT lr = NULL;

        // 現在のスレッドを取得
        currentThreadId = std::this_thread::get_id();

        // /*カレントスレッドの終了時*/
        // if (uMsg == WM_QUIT)
        // {// 0x0012
        //     // アプリケーションの終了(メッセージループ終了)
        //     // PostQuitMessage関数を実行時に発生するが, ここまで処理が来ない.
        //     /**
        //      * @brief 
        //      * WM_QUIT メッセージはウィンドウに関連付けられていないため, 
        //      * ウィンドウのウィンドウ プロシージャを介して受信することはない.
        //      * GetMessage関数またはPeekMessage関数によってのみ取得できる.
        //      * 
        //      * @return return 
        //      */
        //     return LRESULT(NULL);
        // }

        EventDispatcher::AddRef(hWnd);

        /*ウィンドウ生成時*/
        if (uMsg == WM_CREATE)
        {// 0x0001
            // lParamからlpCreateStructを抽出
            LPCREATESTRUCT lpCreateStruct = NULL;
            lpCreateStruct = (LPCREATESTRUCT)lParam;
            if (lpCreateStruct->lpCreateParams != NULL)
            {
                // Widget*とHWNDのマッピングを生成
                widget = (Widget*)lpCreateStruct->lpCreateParams;
                RegisterWidget(hWnd, widget);
                EventDispatcher::AddRef(hWnd);

                // ウィンドウの生成時
                // 注意) CreateWindow()に制御が戻る前に，呼ばれる
                lr = LRESULT(NULL);
            }
        }

        // Widgetのポインタを取得
        widget = GetWidgetPointer(hWnd);

        // ウィンドウメッセージ処理
        switch (uMsg)
        {
            /*対象ウィンドウの削除直前(子ウィンドウが全部削除された直後)*/
            case WM_DESTROY: 
            {// 0x0002
                
            }
            break;
            
            /*対象ウィンドウの削除直後*/
            case WM_NCDESTROY: 
            {// 0x0082
                EventDispatcher::SubRef(hWnd);
                UnreigsterWidget(hWnd);
                
                auto& registryWidget = GetGlobalWidgetMap();
                if (registryWidget.size() == 0)
                {
                    // // カレントスレッドのイベントループを停止
                    // ::PostQuitMessage(0);

                    // EventDispatcherが管理する(カレント&他)スレッドに停止命令を送信
                    auto& registryDispatcher = GetGlobalDispatcherMap();
                    for (const auto& pair : registryDispatcher)
                    {
                        DWORD threadId = pair.second; // NativeはDWORD, 疑似IDはHANDLE型, その他標準は, std::thread::id型
                        bool ret;
                        // 指定したスレッドにメッセージ キューがない場合、関数は失敗
                        ret = PostThreadMessage(threadId, WM_QUIT, 0, 0);
                        if (!ret)
                        {    
                            // re_try
                            PostThreadMessage(threadId, WM_QUIT, 0, 0);
                        }
                    }
                    
                }
            }
            break;

            default:
            {
                // Windows APIのDefWindowProcに処理を任せる
                lr = DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }

        EventDispatcher::SubRef(hWnd); // WM_NCDESTROYを受信していた場合, このタイミングで<=0

        return lr;
    }
}