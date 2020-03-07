#pragma once
#include <functional>

namespace containers::views
{
    template <typename TValue, typename TKey>
    class prefix_view;

    template <typename TValue, typename TKey>
    class postfix_view;

    template <typename TValue, typename TKey>
    class infix_view;
}

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_node
    {
        friend class containers::views::prefix_view<TValue, TKey>;
        friend class containers::views::postfix_view<TValue, TKey>;
        friend class containers::views::infix_view<TValue, TKey>;

    public:
        binary_node(TValue value, std::function<TKey(TValue)> comparer)
                : value_(value), hash_(comparer)
        {
        }

        void value(TValue v) { value_ = v; }

        TValue& value() { return value_; }


        void add(TValue v);
        void remove(TKey key);

        [[nodiscard]] TKey key() { return hash_(value_); }

        [[nodiscard]] const TValue& value() const { return value_; }

        [[nodiscard]] bool exists(TKey k) const;

    private:
        TValue value_;
        std::function<TKey(TValue)> hash_;
        std::unique_ptr<binary_node<TValue, TKey>> left_;
        std::unique_ptr<binary_node<TValue, TKey>> right_;

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
            left_->add(v);
        }
        else
        {
            left_ = std::make_unique<binary_node<TValue, TKey>>(v, hash_);
        }
    }
    else if (k > key())
    {
        if (right_)
        {
            right_->add(v);
        }
        else
        {
            right_ = std::make_unique<binary_node<TValue, TKey>>(v, hash_);
        }
    }
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
        right_remove(v);
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
    return key() < value_ && left_ && left_->exists(k);
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::right_contains(TKey k) const
{
    return key() > value_ && right_ && right_->exists(k);
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::right_remove(TKey k)
{
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::remove_node()
{
}
