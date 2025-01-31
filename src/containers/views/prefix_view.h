#pragma once
#include <stack>
#include "declarations.h"
#include "binary_tree.h"
#include "binary_node.h"
#include "poly_tree.h"

namespace containers::views
{
    template <typename TValue, typename TKey>
    class prefix_view
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

            auto& operator++(); // prefix
            auto operator++(int); // postfix

            // TODO: add decrement operators

            TValue& operator*() { return value(); }

            const TValue& operator*() const { return value(); }

            TValue& value();

            // TODO: add other comparison operators
            [[nodiscard]] bool operator<(const iterator& other) const;

            [[nodiscard]] bool operator==(const iterator& other) const;

            [[nodiscard]] bool operator!=(const iterator& other) const;

            [[nodiscard]] int level() const { return stack_.size(); }

            [[nodiscard]] TKey key() const;

            [[nodiscard]] const TValue& value() const;

        private:
            const containers::binary_tree<TValue, TKey>* tree_;
            std::stack<containers::binary_node<TValue, TKey>*> stack_;

            void first();

            [[nodiscard]] bool has_value() const { return !stack_.empty(); }

            void check_stack_has_values() const;
            void check_has_same_tree(const iterator& other) const;
        };

        prefix_view(const containers::binary_tree<TValue, TKey>* tree) : tree_(tree)
        {
        }

        static void traverse(const containers::binary_node<TValue, TKey>* root,
            std::function<void(const TValue&)> func)
        {
            if (root == nullptr)
            {
                return;
            }

            func(root->value_);
            traverse(root->left_, func);
            traverse(root->right_, func);
        }

        static void traverse(const containers::binary_tree<TValue, TKey>& tree,
            std::function<void(const TValue&)> func)
        {
            traverse(tree.root_, func);
        }

        auto begin() { return iterator(tree_); }

        auto end() { return iterator(tree_, true); }

    private:
        const containers::binary_tree<TValue, TKey>* tree_;
    };

    template <typename TValue, typename TKey>
    auto& prefix_view<TValue, TKey>::iterator::operator++()
    {
        check_stack_has_values();

        auto top = stack_.top();

        // Can move to the left
        if (auto left = top->left_.get())
        {
            stack_.push(left);
        }
        // Can move to the right
        else if (auto right = top->right_.get())
        {
            stack_.push(right);
        }
        // Should go up
        else
        {
            auto prev = top;
            stack_.pop();
            if (!stack_.empty())
            {
                auto node = stack_.top();
                while (!stack_.empty() && (!node->right_ || node->right_.get() == prev))
                {
                    prev = node;
                    node = stack_.top();
                    stack_.pop();
                }

                if (node->right_ && node->right_.get() != prev)
                {
                    stack_.push(node->right_.get());
                }
            }
        }
        return *this;
    }

    template <typename TValue, typename TKey>
    auto prefix_view<TValue, TKey>::iterator::operator++(int)
    {
        // TODO operator++ for iterator
    }

    template <typename TValue, typename TKey>
    void prefix_view<TValue, TKey>::iterator::first()
    {
        if (auto node = tree_->root_.get())
        {
            stack_.push(node);
        }
    }

    template<typename TValue, typename TKey>
    TKey prefix_view<TValue, TKey>::iterator::key() const
    {
        check_stack_has_values();
        return stack_.top()->key();
    }

    template <typename TValue, typename TKey>
    const TValue& prefix_view<TValue, TKey>::iterator::value() const
    {
        check_stack_has_values();
        return stack_.top()->value();
    }

    template <typename TValue, typename TKey>
    void prefix_view<TValue, TKey>::iterator::check_stack_has_values() const
    {
        if (stack_.empty())
        {
            // TODO: stack is empty
            throw std::range_error("Incrementing iterator past the end");
        }
    }

    template <typename TValue, typename TKey>
    TValue& prefix_view<TValue, TKey>::iterator::value()
    {
        check_stack_has_values();
        return stack_.top()->value();
    }

    template <typename TValue, typename TKey>
    bool prefix_view<TValue, TKey>::iterator::operator<(const prefix_view::iterator& other) const
    {
        return has_value()
            && (!other.has_value() || this->key() < other.key());
    }

    template <typename TValue, typename TKey>
    bool prefix_view<TValue, TKey>::iterator::operator==(const prefix_view::iterator& other) const
    {
        return (has_value() && other.has_value() && this->key() == other.key())
            || (!has_value() && !other.has_value());
    }

    template <typename TValue, typename TKey>
    bool prefix_view<TValue, TKey>::iterator::operator!=(const prefix_view::iterator& other) const
    {
        return !this->operator==(other);
    }

    template <typename TValue, typename TKey>
    void prefix_view<TValue, TKey>::iterator::check_has_same_tree(const prefix_view::iterator& other) const
    {
        if (tree_ != other.tree_)
        {
            // TODO: different trees
            throw std::logic_error("Iterators are linked to different trees");
        }
    }
}
