#pragma once
#include <stack>
#include "binary_tree.h"
#include "binary_node.h"

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_tree;
}

namespace containers::views
{
    template <typename TValue, typename TKey>
    class postfix_view
    {
    public:
        class iterator
        {
        public:
            explicit iterator(const containers::binary_tree<TValue, TKey>* tree, bool end = false)
                : tree_(tree)
            {
                if (!end)
                {
                    first();
                }
            }

            iterator& operator++(); // prefix
            iterator operator++(int); // postfix

            // TODO: add decrement operators

            TValue& operator*() { return value(); }

            const TValue& operator*() const { return value(); }

            TValue& value();

            // TODO: add other comparison operators
            [[nodiscard]] bool operator<(const iterator& other) const;

            [[nodiscard]] bool operator==(const iterator& other) const;

            [[nodiscard]] bool operator!=(const iterator& other) const;

            [[nodiscard]] int level() const { return stack_.size(); }

            [[nodiscard]] const TValue& value() const;

        private:
            const containers::binary_tree<TValue, TKey>* tree_;
            std::stack<containers::binary_node<TValue, TKey>*> stack_;

            void first();

            [[nodiscard]] bool has_value() const { return !stack_.empty(); }

            void check_stack_has_values() const;
            void check_has_same_tree(const iterator& other) const;
        };

        postfix_view(const containers::binary_tree<TValue, TKey>* tree) : tree_(tree)
        {
        }

        iterator begin() { return iterator(tree_); }

        iterator end() { return iterator(tree_, true); }

    private:
        const containers::binary_tree<TValue, TKey>* tree_;
    };

    template <typename TValue, typename TKey>
    typename postfix_view<TValue, TKey>::iterator& postfix_view<TValue, TKey>::iterator::operator++()
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
            // Get current node
            auto prev = stack_.top();
            stack_.pop();
            decltype(prev) cur = nullptr;

            if (!stack_.empty())
            {
                cur = stack_.top();
            }

            // Ascend to uppermost node (if exists)
            while (!stack_.empty() && cur->right_ && cur->right_.get() == prev)
            {
                prev = cur;
                stack_.pop();

                // Get parent node if exists
                cur = stack_.empty() ? nullptr : stack_.top();
            }
        }
        return *this;
    }

    template <typename TValue, typename TKey>
    typename postfix_view<TValue, TKey>::iterator postfix_view<TValue, TKey>::iterator::operator++(int)
    {
        // TODO operator++ for iterator
    }

    template <typename TValue, typename TKey>
    void postfix_view<TValue, TKey>::iterator::first()
    {
        auto node = tree_->root_.get();
        while (node)
        {
            stack_.push(node);
            node = node->left_.get();
        }
    }

    template <typename TValue, typename TKey>
    const TValue& postfix_view<TValue, TKey>::iterator::value() const
    {
        check_stack_has_values();
        return stack_.top()->value();
    }

    template <typename TValue, typename TKey>
    void postfix_view<TValue, TKey>::iterator::check_stack_has_values() const
    {
        if (stack_.empty())
        {
            // TODO: stack is empty
            throw std::range_error("Incrementing iterator past the end");
        }
    }

    template <typename TValue, typename TKey>
    TValue& postfix_view<TValue, TKey>::iterator::value()
    {
        check_stack_has_values();
        return stack_.top()->value();
    }

    template <typename TValue, typename TKey>
    bool postfix_view<TValue, TKey>::iterator::operator<(const postfix_view::iterator& other) const
    {
        return has_value()
            && (!other.has_value() || this->value() < other.value());
    }

    template <typename TValue, typename TKey>
    inline bool postfix_view<TValue, TKey>::iterator::operator==(const postfix_view::iterator& other) const
    {
        return (has_value() && other.has_value() && this->value() == other.value())
            || (!has_value() && !other.has_value());
    }

    template <typename TValue, typename TKey>
    inline bool postfix_view<TValue, TKey>::iterator::operator!=(const postfix_view::iterator& other) const
    {
        return !this->operator==(other);
    }

    template <typename TValue, typename TKey>
    void postfix_view<TValue, TKey>::iterator::check_has_same_tree(const postfix_view::iterator& other) const
    {
        if (tree_ != other.tree_)
        {
            // TODO: different trees
            throw std::logic_error("Iterators are linked to different trees");
        }
    }
}
