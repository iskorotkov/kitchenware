#pragma once
#include <functional>
#include "declarations.h"
#include "infix_view.h"
#include "postfix_view.h"
#include "prefix_view.h"
#include "red_black.h"

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_node
    {
        friend class containers::views::prefix_view<TValue, TKey>;
        friend class containers::views::postfix_view<TValue, TKey>;
        friend class containers::views::infix_view<TValue, TKey>;

        friend class containers::balancing::red_black<TValue, TKey>;

    public:
        binary_node(TValue value,
            std::function<TKey(const TValue&)> hash)
                : value_(std::move(value)),
                  hash_(hash)
        {
        }

        [[nodiscard]] TKey key() const { return hash_(value_); }

        [[nodiscard]] const TValue& value() const { return value_; }

        [[nodiscard]] bool exists(TKey k) const;

        ~binary_node();

    private:
        TValue value_;
        std::function<TKey(const TValue&)> hash_;
        binary_node<TValue, TKey>* left_ = nullptr;
        binary_node<TValue, TKey>* right_ = nullptr;
        binary_node<TValue, TKey>* parent_ = nullptr;

        uint8_t tag_;

        [[nodiscard]] bool left_contains(TKey k) const;
        [[nodiscard]] bool right_contains(TKey k) const;
    };
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::exists(TKey k) const
{
    return key() == k || left_contains(k) || right_contains(k);
}

template<typename TValue, typename TKey>
containers::binary_node<TValue, TKey>::~binary_node()
{
    if (left_)
    {
        delete left_;
    }
    if (right_)
    {
        delete right_;
    }
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::left_contains(TKey k) const
{
    return k < key() && left_ && left_->exists(k);
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::right_contains(TKey k) const
{
    return k > key() && right_ && right_->exists(k);
}
