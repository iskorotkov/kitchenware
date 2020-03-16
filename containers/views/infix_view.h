#pragma once
#include <stack>
#include "declarations.h"
#include "binary_tree.h"
#include "binary_node.h"
#include "poly_tree.h"

namespace containers::views
{
    template <typename TValue, typename TKey>
    class infix_view
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
                    subtree_first(tree_->root_);
                }
            }

            auto& operator++();   // prefix
            auto operator++(int); // postfix

            // TODO: add decrement operators

            const TValue& operator*() const { return value(); }

            [[nodiscard]] bool operator==(const iterator& other) const;

            [[nodiscard]] bool operator!=(const iterator& other) const;

            [[nodiscard]] TKey key() const;

            [[nodiscard]] const TValue& value() const;

        private:
            const containers::binary_tree<TValue, TKey>* tree_;
            const binary_node<TValue, TKey>* node_ = nullptr;

            void subtree_first(const binary_node<TValue, TKey>* node);

            [[nodiscard]] bool has_value() const { return node_ != nullptr; }

            void check_has_values() const;
            void check_has_same_tree(const iterator& other) const;
        };

        infix_view(const containers::binary_tree<TValue, TKey>* tree) : tree_(tree)
        {
        }

        static void traverse(const containers::binary_node<TValue, TKey>* root,
            std::function<void(const TValue&)> func)
        {
            if (root == nullptr)
            {
                return;
            }

            traverse(root->left_);
            func(root->value_);
            traverse(root->right_);
        }

        static void traverse(const containers::binary_tree<TValue, TKey>& tree,
            std::function<void(const TValue&)> func)
        {
            traverse(tree.root_, func);
        }

        auto begin() { return iterator(tree_, false); }

        auto end() { return iterator(tree_, true); }

    private:
        const containers::binary_tree<TValue, TKey>* tree_;
    };

    template <typename TValue, typename TKey>
    auto& infix_view<TValue, TKey>::iterator::operator++()
    {
        check_has_values();

        if (node_->right_)
        {
            node_ = node_->right_;
            subtree_first(node_);
        }
        else if (node_->parent_ && node_->parent_->right_ == node_)
        {
            auto prev = node_;
            node_ = node_->parent_;
            while (node_ && node_->right_ == prev)
            {
                prev = node_;
                node_ = node_->parent_;
            }
        }
        //else if (node_->parent_ && node_->parent_->left_ == node_)
        //{
        //    node_ = node_->parent_;
        //}
        else
        {
            node_ = node_->parent_;
        }

        return *this;
    }

    template <typename TValue, typename TKey>
    auto infix_view<TValue, TKey>::iterator::operator++(int)
    {
        auto copy = *this;
        operator++();
        return copy;
    }

    template <typename TValue, typename TKey>
    void infix_view<TValue, TKey>::iterator::subtree_first(const binary_node<TValue, TKey>* node)
    {
        node_ = node;
        while (node && node_->left_)
        {
            node_ = node_->left_;
        }
    }

    template <typename TValue, typename TKey>
    TKey infix_view<TValue, TKey>::iterator::key() const
    {
        check_has_values();
        return node_->key();
    }

    template <typename TValue, typename TKey>
    const TValue& infix_view<TValue, TKey>::iterator::value() const
    {
        check_has_values();
        return node_->value();
    }

    template <typename TValue, typename TKey>
    void infix_view<TValue, TKey>::iterator::check_has_values() const
    {
        if (node_ == nullptr)
        {
            throw std::range_error("Incrementing iterator past the end");
        }
    }

    template <typename TValue, typename TKey>
    inline bool infix_view<TValue, TKey>::iterator::operator==(const infix_view::iterator& other) const
    {
        return (has_value() && other.has_value() && key() == other.key())
        || (!has_value() && !other.has_value());
    }

    template <typename TValue, typename TKey>
    inline bool infix_view<TValue, TKey>::iterator::operator!=(const infix_view::iterator& other) const
    {
        return !this->operator==(other);
    }

    template <typename TValue, typename TKey>
    void infix_view<TValue, TKey>::iterator::check_has_same_tree(const infix_view::iterator& other) const
    {
        if (tree_ != other.tree_)
        {
            // TODO: different trees
            throw std::logic_error("Iterators are linked to different trees");
        }
    }
}
