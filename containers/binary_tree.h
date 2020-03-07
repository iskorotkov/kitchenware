#pragma once
#include <memory>
#include <functional>
#include "binary_node.h"
#include "prefix_view.h"

namespace containers
{
    template <typename T>
    class binary_tree final
    {
        friend class views::prefix_view<T>;

    public:
        binary_tree() = default;

        explicit binary_tree(std::function<int(T, T)> comparer) : comparer_(comparer)
        {
        }

        void add(T value);
        void remove(T value);
        [[nodiscard]] bool exists(T value) const;

        [[nodiscard]] views::prefix_view<T> create_prefix_view() const { return views::prefix_view<T>(this); }

        // TODO: Add views
//        [[nodiscard]] infix_view create_infix_view() const;
//        [[nodiscard]] postfix_view create_postfix_view() const;

    private:
        std::unique_ptr<binary_node<T>> root_;
        std::function<int(T, T)> comparer_;
    };
}

template <typename T>
void containers::binary_tree<T>::remove(T value)
{
    if (auto root = root_.get())
    {
        root->remove(value);
    }
}

template <typename T>
bool containers::binary_tree<T>::exists(T value) const
{
    if (const auto root = root_.get())
    {
        return root->exists(value);
    }
    return false;
}

template <typename T>
void containers::binary_tree<T>::add(T value)
{
    if (auto root = root_.get())
    {
        root->add(value);
    }
    else
    {
        root_ = std::make_unique<binary_node<T>>(value, comparer_);
    }
}
