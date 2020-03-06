#pragma once
#include <stack>
#include <binary_tree.h>
#include "binary_tree.h"
#include "binary_node.h"

namespace containers
{
    template <typename T>
    class binary_tree;
}

namespace views
{
    template <typename T>
    class prefix_view
    {
    public:
        class const_iterator
        {
        public:
            explicit const_iterator(const containers::binary_tree<T>* tree, bool end = false)
                    : tree_(tree)
            {
                if (!end)
                {
                    first();
                }
            }

            const_iterator& operator++(); // prefix
            const_iterator operator++(int); // postfix

            // TODO: add decrement operators

            T operator*() const;

            // TODO: add other comparison operators
            [[nodiscard]] bool operator<(const prefix_view::const_iterator& other) const;

            [[nodiscard]] int level() const { return stack_.size(); }

            [[nodiscard]] T value() const;

        private:
            const containers::binary_tree<T>* tree_;
            std::stack<containers::binary_node<T>*> stack_;

            void first();

            [[nodiscard]] bool has_value() const { return !stack_.empty(); }

            void check_stack_has_values() const;
            void check_has_same_tree(const const_iterator& other) const;
        };

        class const_reverse_iterator
        {
        };

        prefix_view(const containers::binary_tree<T>* tree) : tree_(tree)
        {
        }

        virtual const_iterator cbegin() const { return const_iterator(tree_); }

        virtual const_iterator cend() const { return const_iterator(tree_, true); }

//        virtual const_reverse_iterator<T> crbegin() const;
//        virtual const_reverse_iterator<T> crend() const;

    private:
        const containers::binary_tree<T>* tree_;
    };

    template <typename T>
    typename prefix_view<T>::const_iterator& prefix_view<T>::const_iterator::operator++()
    {
        check_stack_has_values();

        // Can move to the right
        if (auto node = stack_.top()->right_.get())
        {
            // Add every value in left subtrees and descend to the left-most node
            while (node)
            {
                stack_.push(node);
                node = node->left_.get();
            }
        }
        else
        {
            auto prev = stack_.top();
            stack_.pop();
            decltype(prev) cur = nullptr;
            if (!stack_.empty())
            {
                cur = stack_.top();
            }
            while (!stack_.empty() && cur->right_ && cur->right_.get() == prev)
            {
                prev = cur;
                cur = stack_.top();
                stack_.pop();
            }
        }
        return *this;
    }

    template <typename T>
    typename prefix_view<T>::const_iterator prefix_view<T>::const_iterator::operator++(int)
    {
    }

    template <typename T>
    void prefix_view<T>::const_iterator::first()
    {
        auto node = tree_->root_.get();
        while (node)
        {
            stack_.push(node);
            node = node->left_.get();
        }
    }

    template <typename T>
    T prefix_view<T>::const_iterator::operator*() const
    {
        return value();
    }

    template <typename T>
    T prefix_view<T>::const_iterator::value() const
    {
        check_stack_has_values();
        return stack_.top()->value();
    }

    template <typename T>
    void prefix_view<T>::const_iterator::check_stack_has_values() const
    {
        if (stack_.empty())
        {
            // TODO: stack is empty
            throw std::range_error("Incrementing iterator past the end");
        }
    }

    template <typename T>
    bool prefix_view<T>::const_iterator::operator<(const prefix_view::const_iterator& other) const
    {
        return has_value()
               && (!other.has_value() || this->value() < other.value());
    }

    template <typename T>
    void prefix_view<T>::const_iterator::check_has_same_tree(const prefix_view::const_iterator& other) const
    {
        if (tree_ != other.tree_)
        {
            // TODO: different trees
            throw std::logic_error("Iterators are linked to different trees");
        }
    }
}
