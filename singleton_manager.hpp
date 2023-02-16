/**
 * @file singleton_manager-internal.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <singleton_manager-internal.hpp>
#include <rtti.hpp>

namespace is
{
    template <typename SINGLETON>
    SINGLETON *SingletonManager::Get()
    {
        // 内部リンケージのstatic変数は必ずdll側の*.cppで定義すること.
        // https://qiita.com/Chironian/items/3fb61cffa2a20dbee5c2
        std::mutex &mtx = SingletonManager::GetMutex();

        // クリティカルセクション作成
        std::lock_guard<std::mutex> locker(mtx);

        static SINGLETON *instance{nullptr}; // 初回だけnullptrで初期化される
        if (instance)
        {
            return instance;
        }

        SingletonManager &self = SingletonManager::GetSelf();
        instance = new SINGLETON{};
        IS_SINGLETON_LOG(Create, SINGLETON)

        auto deleter = [&]() -> void
        {
            IS_SINGLETON_LOG(Delete, SINGLETON)
            delete instance;
            instance = nullptr;
        };

        int id = self.mCount;
        self.mSingletons.insert({id, {(uintptr_t)instance, deleter}}); // Register deleter
        self.mAddress2Id.insert({(uintptr_t)instance, id});            // Register ID
        self.mCount += 1;
        return instance;
    }

    template <typename SINGLETON>
    int SingletonManager::GetId()
    {
        SingletonManager &self = SingletonManager::GetSelf();
        auto address = (uintptr_t)(Get<SINGLETON>());
        return self.mAddress2Id[address];
    }

    template <typename SINGLETON>
    void SingletonManager::Erase()
    {
        EraseById(GetId<SINGLETON>());
    }
}