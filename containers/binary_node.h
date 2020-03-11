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
        binary_node(TValue& value,
            binary_node<TValue, TKey>* parent,
            std::function<TKey(const TValue&)> hash)
                : value_(std::move(value)),
                  parent_(parent),
                  hash_(hash)
        {
        }

        TValue& value() { return value_; }

        void add(TValue v);
        void remove(TKey key);

        [[nodiscard]] binary_node<TValue, TKey>* left() const { return left_.get(); }
        [[nodiscard]] binary_node<TValue, TKey>* right() const { return right_.get(); }

        [[nodiscard]] TKey key() const { return hash_(value_); }

        [[nodiscard]] const TValue& value() const { return value_; }

        [[nodiscard]] bool exists(TKey k) const;

    private:
        TValue value_;
        std::function<TKey(const TValue&)> hash_;
        std::unique_ptr<binary_node<TValue, TKey>> left_;
        std::unique_ptr<binary_node<TValue, TKey>> right_;

        bool is_black_ = true;
        binary_node<TValue, TKey>* parent_;
        balancing::red_black<TValue, TKey> balancer_;

        [[nodiscard]] bool left_contains(TKey k) const;
        [[nodiscard]] bool right_contains(TKey k) const;

        [[nodiscard]] bool has_children() const { return left_ || right_; }

        [[nodiscard]] bool has_both_children() const { return left_ && right_; }

        [[nodiscard]] bool has_left_child() const { return left_; }

        [[nodiscard]] bool has_right_child() const { return right_; }

        void left_remove(TKey k);
        void right_remove(TKey k);
        void remove_node();
    };
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::add(TValue v)
{
    auto k = hash_(v);
    if (k < key())
    {
        if (left_)
        {
            left_->add(std::move(v));
        }
        else
        {
            left_ = std::make_unique<binary_node<TValue, TKey>>(v, this, hash_);
        }
    }
    else if (k > key())
    {
        if (right_)
        {
            right_->add(std::move(v));
        }
        else
        {
            right_ = std::make_unique<binary_node<TValue, TKey>>(v, this, hash_);
        }
    }
    balancer_.insert_case1(this);
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::remove(TKey k)
{
    if (k < key())
    {
        left_remove(k);
    }
    else if (k > key())
    {
        right_remove(k);
    }
    else // v == value_
    {
        remove_node();
    }
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::left_remove(TKey k)
{
    if (this->left_)
    {
        if (this->left_->value_ == k)
        {
            if (!this->left_->has_children())
            {
                this->left_.reset();
            }
        }
    }
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::exists(TKey k) const
{
    return key() == k || left_contains(k) || right_contains(k);
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

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::right_remove(TKey k)
{
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::remove_node()
{
}
