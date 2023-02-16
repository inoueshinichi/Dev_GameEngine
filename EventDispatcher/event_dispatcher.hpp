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

namespace is
{
    // シングルトンクラス
    class IS_WIN_API EventDispatcher
    {
    public:
        virtual ~EventDispatcher() {}
        virtual const TCHAR *GetClassName() const override { return _T("EventDispatcher"); }
    private:
        friend class SingletonManager;
        EventDispatcher();

        IS_DISABLE_COPY_AND_ASSIGN(EventDispatcher)
    };
}