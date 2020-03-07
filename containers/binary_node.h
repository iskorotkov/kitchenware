#pragma once
#include <functional>

namespace containers::views
{
    template <typename TValue, typename TKey>
    class prefix_view;
}

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_node
    {
        friend class containers::views::prefix_view<TValue, TKey>;

    public:
        binary_node(TValue value, std::function<TKey(TValue)> comparer)
                : value_(value), hash_(comparer)
        {
        }

        void value(TValue v) { value_ = v; }

        TValue& value() { return value_; }

        void add(TValue v);
        void remove(TValue v);

        [[nodiscard]] const TValue& value() const { return value_; }

        [[nodiscard]] bool exists(TValue v) const;

    private:
        TValue value_;
        std::function<TKey(TValue)> hash_;
        std::unique_ptr<binary_node<TValue, TKey>> left_;
        std::unique_ptr<binary_node<TValue, TKey>> right_;

        [[nodiscard]] bool left_contains(TValue v) const;
        [[nodiscard]] bool right_contains(TValue v) const;

        [[nodiscard]] bool has_children() const { return left_ || right_; }

        [[nodiscard]] bool has_both_children() const { return left_ && right_; }

        [[nodiscard]] bool has_left_child() const { return left_; }

        [[nodiscard]] bool has_right_child() const { return right_; }

        void left_insert(TValue v);
        void right_insert(TValue v);
        void remove_node();
    };
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::add(TValue v)
{
    if (v < value_)
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
    else if (v > value_)
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
void containers::binary_node<TValue, TKey>::remove(TValue v)
{
    if (v < value_)
    {
        left_insert(v);
    }
    else if (v > value_)
    {
        right_insert(v);
    }
    else // v == value_
    {
        remove_node();
    }
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::left_insert(TValue v)
{
    if (this->left_)
    {
        if (this->left_->value_ == v)
        {
            if (!this->left_->has_children())
            {
                this->left_.reset();
            }
        }
    }
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::exists(TValue v) const
{
    return value_ == v || left_contains(v) || right_contains(v);
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::left_contains(TValue v) const
{
    return v < value_ && left_ && left_->exists(v);
}

template <typename TValue, typename TKey>
bool containers::binary_node<TValue, TKey>::right_contains(TValue v) const
{
    return v > value_ && right_ && right_->exists(v);
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::right_insert(TValue v)
{
}

template <typename TValue, typename TKey>
void containers::binary_node<TValue, TKey>::remove_node()
{
}
