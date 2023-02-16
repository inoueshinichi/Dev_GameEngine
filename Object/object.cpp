#include <object.hpp>

namespace is
{
    Object::Object(Object *parent)
        : mParent(parent)
    {
        if (mParent)
        {
            mParent->AddChild(this);
        }
    }

    Object::~Object()
    {
        while (!mChildren.empty())
        {
            delete mChildren.back();
        }

        if (mParent)
        {
            mParent->RemoveChild(this);
        }
    }

    void Object::AddChild(Object *child)
    {
        mChildren.emplace_back(child);
    }

    void Object::RemoveChild(Object *child)
    {
        auto iter = std::find(mChildrent.begin(), mChildrent.end(), child);
        if (iter != mChildren.end())
        {
            std::iter_swap(iter, mChildren.end() - 1);
            mChildren.pop_back();
        }
    }
}