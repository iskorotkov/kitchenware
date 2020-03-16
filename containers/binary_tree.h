#pragma once
#include <memory>
#include <functional>
#include "declarations.h"
#include "binary_node.h"
#include "infix_view.h"
#include "postfix_view.h"
#include "prefix_view.h"

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_tree
    {
        friend class views::prefix_view<TValue, TKey>;
        friend class views::postfix_view<TValue, TKey>;
        friend class views::infix_view<TValue, TKey>;

    public:
        binary_tree() : hash_([](auto value) { return value; })
        {
        }

        explicit binary_tree(std::function<TKey(const TValue&)> hash) : hash_(hash)
        {
        }

        void add(TValue value);
        void remove(TKey key);
        void clear();
        [[nodiscard]] bool exists(TKey key) const;

        // [[nodiscard]] auto create_prefix_view() const { return views::prefix_view<TValue, TKey>(this); }
        [[nodiscard]] auto create_infix_view() const { return views::infix_view<TValue, TKey>(this); }
        // [[nodiscard]] auto create_postfix_view() const { return views::postfix_view<TValue, TKey>(this); };

        virtual ~binary_tree() { clear(); }

    private:
        binary_node<TValue, TKey>* root_ = nullptr;
        std::function<TKey(const TValue&)> hash_;
        balancing::red_black<TValue, TKey> balancer_;
    };
}

template <typename TValue, typename TKey>
void containers::binary_tree<TValue, TKey>::remove(TKey key)
{
    balancer_.remove(root_, key);
}

template<typename TValue, typename TKey>
void containers::binary_tree<TValue, TKey>::clear()
{
    if (root_)
    {
        delete root_;
        root_ = nullptr;
    }
}

template <typename TValue, typename TKey>
bool containers::binary_tree<TValue, TKey>::exists(TKey key) const
{
    if (root_)
    {
        return root_->exists(key);
    }
    return false;
}

template <typename TValue, typename TKey>
void containers::binary_tree<TValue, TKey>::add(TValue value)
{
    balancer_.add(root_, value, hash_);
}
