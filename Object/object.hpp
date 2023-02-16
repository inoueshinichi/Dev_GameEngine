/**
 * @file object.hpp
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

namespace is
{
    using ObjectList = std::vector<Object*>;

    class IS_WIN_API IObject
    {
    public:
        virtual ~Interface() {}
        virtual const TCHAR *GetClassName() const = 0;
    };

    /**
     * @brief 全クラスの基底&抽象インターフェース
     * 
     */
    class IS_WIN_API Object : IObject
    {
    public:
        Object(Object *parent = nullptr);
        virtual ~Object();
        virtual const TCHAR* GetClassName() const override { return _T("Object"); }

        const ObjectList &GetChildren() const { return mChildren; }
        Object* GetParent() const { return mParent; }

        void AddChild(Object *child);
        void RemoveChild(Object *child);

    protected:
    private:
        Object* mParent;
        ObjectList mChildren;

        IS_DISABLE_COPY_AND_ASSIGN(Object)
    };
}