#pragma once
#include <stack>
#include "declarations.h"
#include "binary_tree.h"
#include "binary_node.h"

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

            auto& operator++();   // prefix
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

        postfix_view(const containers::binary_tree<TValue, TKey>* tree) : tree_(tree)
        {
        }

        auto begin() { return iterator(tree_); }

        auto end() { return iterator(tree_, true); }

    private:
        const containers::binary_tree<TValue, TKey>* tree_;
    };

    template <typename TValue, typename TKey>
    auto& postfix_view<TValue, TKey>::iterator::operator++()
    {
        check_stack_has_values();

        auto cur = stack_.top();
        stack_.pop();

        // Traverse isn't finished
        if (!stack_.empty())
        {
            auto parent = stack_.top();

            // Left subtree
            if (parent->left_.get() == cur)
            {
                auto node = parent->right_.get();
                while (node)
                {
                    stack_.push(node);
                    if (node->left_)
                    {
                        node = node->left_.get();
                    }
                    else if (node->right_)
                    {
                        node = node->right_.get();
                    }
                    else
                    {
                        node = nullptr;
                    }
                }
            }
        }

        return *this;
    }

    template <typename TValue, typename TKey>
    auto postfix_view<TValue, TKey>::iterator::operator++(int)
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
            if (node->left_)
            {
                node = node->left_.get();
            }
            else if (node->right_)
            {
                node = node->right_.get();
            }
            else
            {
                node = nullptr;
            }
        }
    }

    template<typename TValue, typename TKey>
    TKey postfix_view<TValue, TKey>::iterator::key() const
    {
        check_stack_has_values();
        return stack_.top()->key();
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
        && (!other.has_value() || this->key() < other.key());
    }

    template <typename TValue, typename TKey>
    inline bool postfix_view<TValue, TKey>::iterator::operator==(const postfix_view::iterator& other) const
    {
        return (has_value() && other.has_value() && this->key() == other.key())
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
