#include "singleton_manager-internal.hpp"

namespace is
{
    // 静的初期化
    SingletonManager *SingletonManager::sSelf = nullptr;

    std::mutex &SingletonManager::GetMutex()
    {
        // 内部リンケージ
        static std::mutex sMtx;
        return sMtx;
    }

    SingletonManager::SingletonManager() {}

    SingletonManager::~SingletonManager() {}

    SingletonManager &SingletonManager::GetSelf()
    {
        if (!sSelf)
        {
            sSelf = new SingletonManager{};
        }
        return *sSelf;
    }

    void SingletonManager::Clear()
    {
        SingletonManager &self = SingletonManager::GetSelf();
        for (int i = 0; i < self.mCount; ++i)
        {
            // Singletonインスタンスを破棄
            EraseById(i);
        }

        // clear
        self.mSingletons.clear();
        self.mAddress2Id.clear();
        self.mCount = 0;
    }

    void SingletonManager::EraseById(int id)
    {
        SingletonManager &self = SingletonManager::GetSelf();
        auto iter = self.mSingletons.find(id);
        if (iter == self.mSingletons.end())
        {
            return;
        }

        iter->second.second(); // Invoke deleter
        self.mAddress2Id.erase(iter->second.first);
        self.mSingletons.erase(iter);
    }
}