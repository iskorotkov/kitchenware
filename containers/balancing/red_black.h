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
            if (g == nullptr) { return nullptr; }
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

            if (pivot->left())
            {
                pivot->left()->parent_ = n;
            }
            n->right_ = std::move(pivot->left_);
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

            if (pivot->right())
            {
                pivot->right()->parent_ = n;
            }
            n->left_ = std::move(pivot->right_);
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

        node_t* sibling(node_t* n)
        {
            if (n == n->parent_->left())
            {
                return n->parent_->right();
            }
            else
            {
                return n->parent_->left();
            }
        }

        void replace_node(node_t* n, node_t* child)
        {
            if (child)
            {
                child->parent_ = n->parent_;
            }
            if (n == n->parent_->left())
            {
                n->parent_->left_.release();
                n->parent_->left_.reset(child);
            }
            else
            {
                n->parent_->right_.release();
                n->parent_->right_.reset(child);
            }
        }

        bool is_leaf(node_t* n)
        {
            return n->left() == nullptr
                && n->right() == nullptr;
        }

        void delete_one_child(node_t* n)
        {
            node_t* child = is_leaf(n) ? n->left() : n->right();
            replace_node(n, child);
            if (n->is_black_ && child)
            {
                if (!child->is_black_)
                {
                    child->is_black_ = true;
                }
                else
                {
                    delete_case1(child);
                }
            }
        }

        void delete_case1(node_t* n)
        {
            if (n->parent_)
            {
                delete_case2(n);
            }
        }

        void delete_case2(node_t* n)
        {
            auto s = sibling(n);
            if (!s->is_black_)
            {
                n->parent_->is_black_ = false;
                s->is_black_ = true;
                if (n == n->parent_->left())
                {
                    rotate_left(n->parent_);
                }
                else
                {
                    rotate_right(n->parent_);
                }
            }
            delete_case3(n);
        }

        void delete_case3(node_t* n)
        {
            auto s = sibling(n);
            if (n->parent_->is_black_
                && s->is_black_
                && s->left()->is_black_
                && s->right()->is_black_)
            {
                s->is_black_ = false;
                delete_case1(n->parent_);
            }
            else
            {
                delete_case4(n);
            }
        }

        void delete_case4(node_t* n)
        {
            auto s = sibling(n);
            if (!n->parent_->is_black_
                && s->is_black_
                && s->left()->is_black_
                && s->right()->is_black_)
            {
                s->is_black_ = false;
                n->parent_->is_black_ = true;
            }
            else
            {
                delete_case5(n);
            }
        }

        void delete_case5(node_t* n)
        {
            auto s = sibling(n);
            if (s->is_black_)
            {
                if (n == n->parent_->left()
                    && s->right()->is_black_
                    && !s->left()->is_black_)
                {
                    s->is_black_ = false;
                    s->left()->is_black_ = true;
                    rotate_right(s);
                }
                else if (n == n->parent_->right()
                    && s->left()->is_black_
                    && !s->right()->is_black_)
                {
                    s->is_black_ = false;
                    s->right()->is_black_ = true;
                    rotate_left(s);
                }
            }
            delete_case6(n);
        }

        void delete_case6(node_t* n)
        {
            auto s = sibling(n);
            s->is_black_ = n->parent_->is_black_;
            n->parent_->is_black_ = true;
            if (n == n->parent_->left())
            {
                s->right()->is_black_ = true;
                rotate_left(n->parent_);
            }
            else
            {
                s->left()->is_black_ = true;
                rotate_right(n->parent_);
            }
        }
    };
}