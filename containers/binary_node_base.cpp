#include "binary_node_base.h"

containers::binary_node_base::binary_node_base(value_ptr value,
    std::function<key_ptr(const value_ptr&)> comparer,
    deleter_t deleter)
    : value_(std::move(value)),
    hash_(comparer),
    deleter_(deleter)
{
}

void containers::binary_node_base::value(value_ptr v)
{
    value_ = std::move(v);
}

void containers::binary_node_base::add(value_ptr v)
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
            left_ = std::make_unique<binary_node_base>(std::move(v), hash_, deleter_);
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
            right_ = std::make_unique<binary_node_base>(std::move(v), hash_, deleter_);
        }
    }
}

void containers::binary_node_base::remove(key_ptr k)
{
    if (k < key())
    {
        left_remove(std::move(k));
    }
    else if (k > key())
    {
        right_remove(std::move(k));
    }
    else
    {
        remove_node();
    }
}

containers::binary_node_base::key_ptr containers::binary_node_base::key() const
{
    return hash_(value_);
}

const  containers::binary_node_base::value_ptr& containers::binary_node_base::value() const
{
    return value_;
}

bool containers::binary_node_base::has_left_child() const
{
    return left_.get();
}

bool containers::binary_node_base::has_right_child() const
{
    return right_.get();
}

void containers::binary_node_base::left_remove(key_ptr k)
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

bool containers::binary_node_base::exists(const key_ptr& k) const
{
    return key() == k || left_contains(k) || right_contains(k);
}

bool containers::binary_node_base::left_contains(const key_ptr& k) const
{
    return key() < value_ && left_ && left_->exists(k);
}

bool containers::binary_node_base::right_contains(const key_ptr& k) const
{
    return key() > value_ && right_ && right_->exists(k);
}

bool containers::binary_node_base::has_both_children() const
{
    return left_ && right_;
}

bool containers::binary_node_base::has_children() const
{
    return left_ || right_;
}

void containers::binary_node_base::right_remove(key_ptr k)
{
}

void containers::binary_node_base::remove_node()
{
}