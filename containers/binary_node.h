#pragma once
#include <functional>

namespace views
{
    template <typename T>
    class prefix_view;
}

namespace containers
{
    template <typename T>
    class binary_node
    {
        friend class views::prefix_view<T>;

    public:
        binary_node(T value, std::function<int(T, T)> comparer)
                : value_(value), comparer_(comparer)
        {
        }

        void value(T v) { value_ = v; }

        T& value() { return value_; }

        void add(T v);
        void remove(T v);

        [[nodiscard]] const T& value() const { return value_; }

        [[nodiscard]] bool exists(T v) const;

    private:
        T value_;
        std::function<int(T, T)> comparer_;
        std::unique_ptr<binary_node<T>> left_;
        std::unique_ptr<binary_node<T>> right_;

        [[nodiscard]] bool left_contains(T v) const;
        [[nodiscard]] bool right_contains(T v) const;

        [[nodiscard]] bool has_children() const { return left_ || right_; }

        [[nodiscard]] bool has_both_children() const { return left_ && right_; }

        [[nodiscard]] bool has_left_child() const { return left_; }

        [[nodiscard]] bool has_right_child() const { return right_; }

        void left_insert(T v);
        void right_insert(T v);
        void remove_node();
    };
}

template <typename T>
void containers::binary_node<T>::add(T v)
{
    if (v < value_)
    {
        if (left_)
        {
            left_->add(v);
        }
        else
        {
            left_ = std::make_unique<binary_node<T>>(v, comparer_);
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
            right_ = std::make_unique<binary_node<T>>(v, comparer_);
        }
    }
}

template <typename T>
void containers::binary_node<T>::remove(T v)
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

template <typename T>
void containers::binary_node<T>::left_insert(T v)
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

template <typename T>
bool containers::binary_node<T>::exists(T v) const
{
    return value_ == v || left_contains(v) || right_contains(v);
}

template <typename T>
bool containers::binary_node<T>::left_contains(T v) const
{
    return v < value_ && left_ && left_->exists(v);
}

template <typename T>
bool containers::binary_node<T>::right_contains(T v) const
{
    return v > value_ && right_ && right_->exists(v);
}

template <typename T>
void containers::binary_node<T>::right_insert(T v)
{
}

template <typename T>
void containers::binary_node<T>::remove_node()
{
}
