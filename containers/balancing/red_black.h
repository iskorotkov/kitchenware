#pragma once
#include <memory>
#include "declarations.h"
#include "binary_node.h"

namespace containers::balancing
{
    template <typename TValue, typename TKey>
    class red_black
    {
    public:
        using node_t = containers::binary_node<TValue, TKey>;

        node_t* grandparent(node_t* n)
        {
            return n && n->parent_
                ? n->parent_->parent_
                : nullptr;
        }

        node_t* uncle(node_t* n)
        {
            auto g = grandparent(n);
            if (!g) { return nullptr; }
            if (n->parent_ == g->left())
            {
                return g->right();
            }
            else
            {
                return g->left();
            }
        }

        void rotate_left(node_t* n)
        {
            node_t* pivot = n->right_.release();
            pivot->parent_ = n->parent_;
            if (n->parent_)
            {
                if (n->parent_->left() == n)
                {
                    n->parent_->left_.release();
                    n->parent_->left_.reset(pivot);
                }
                else
                {
                    n->parent_->right_.release();
                    n->parent_->right_.reset(pivot);
                }
            }

            n->right_.reset(pivot->left_.release());
            if (pivot->left())
            {
                pivot->left()->parent_ = n;
            }
            n->parent_ = pivot;
            pivot->left_.reset(n);
        }

        void rotate_right(node_t* n)
        {
            node_t* pivot = n->left_.release();
            pivot->parent_ = n->parent_;
            if (n->parent_)
            {
                if (n->parent_->left() == n)
                {
                    n->parent_->left_.release();
                    n->parent_->left_.reset(pivot);
                }
                else
                {
                    n->parent_->right_.release();
                    n->parent_->right_.reset(pivot);
                }
            }

            n->left_.reset(pivot->right_.release());
            if (pivot->right())
            {
                pivot->right()->parent_ = n;
            }
            n->parent_ = pivot;
            pivot->right_.reset(n);
        }

        void insert_case1(node_t* n)
        {
            if (n->parent_ == nullptr)
            {
                n->is_black_ = true;
            }
            else
            {
                insert_case2(n);
            }
        }

        void insert_case2(node_t* n)
        {
            if (!n->parent_->is_black_)
            {
                insert_case3(n);
            }
        }

        void insert_case3(node_t* n)
        {
            auto u = uncle(n);
            if (u && !u->is_black_)
            {
                n->parent_->is_black_ = true;
                n->is_black_ = true;
                auto g = n->parent_->parent_;
                g->is_black_ = false;
                insert_case1(g);
            }
            else
            {
                insert_case4(n);
            }
        }

        void insert_case4(node_t* n)
        {
            auto g = grandparent(n);
            if (n == n->parent_->right()
                && n->parent_ == g->left())
            {
                rotate_left(n->parent_);
                n = n->left();
            }
            else if (n == n->parent_->left()
                && n->parent_ == g->right())
            {
                rotate_right(n->parent_);
                n = n->right();
            }
            insert_case5(n);
        }

        void insert_case5(node_t* n)
        {
            auto g = grandparent(n);
            n->parent_->is_black_ = true;
            g->is_black_ = false;
            if (n == n->parent_->left()
                && n->parent_ == g->left())
            {
                rotate_right(g);
            }
            else
            {
                rotate_left(g);
            }
        }
    };
}