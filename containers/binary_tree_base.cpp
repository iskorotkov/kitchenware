#include "binary_tree_base.h"

containers::binary_tree_base::binary_tree_base(std::function<key_ptr(const value_ptr&)> comparer, deleter_t deleter) :
    hash_(comparer),
    deleter_(deleter)
{
}

void containers::binary_tree_base::remove(key_ptr key)
{
    if (auto root = root_.get())
    {
        root->remove(std::move(key));
    }
}

bool containers::binary_tree_base::exists(key_ptr key) const
{
    if (const auto root = root_.get())
    {
        return root->exists(std::move(key));
    }
    return false;
}

void containers::binary_tree_base::add(value_ptr value)
{
    if (auto root = root_.get())
    {
        root->add(std::move(value));
    }
    else
    {
        root_ = std::make_unique<binary_node_base>(std::move(value), hash_, deleter_);
    }
}
