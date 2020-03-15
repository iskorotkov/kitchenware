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
        
        enum color : uint8_t
        {
            black,
            red
        };

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
            if (n->parent_ == g->left_)
            {
                return g->right_;
            }
            else
            {
                return g->left_;
            }
        }

        node_t* insert(node_t* root, node_t* pt)
        {
            if (root == nullptr)
            {
                return pt;
            }

            if (pt->key() < root->key())
            {
                root->left_ = insert(root->left_, pt);
                root->left_->parent_ = root;
            }
            else if (pt->key() > root->key())
            {
                root->right_ = insert(root->right_, pt);
                root->right_->parent_ = root;
            }

            return root;
        }

        void rotate_left(node_t*& root, node_t*& pt)
        {
            auto pt_right = pt->right_;
            pt->right_ = pt_right->left_;

            if (pt->right_)
            {
                pt->right_->parent_ = pt;
            }

            pt_right->parent_ = pt->parent_;

            if (pt->parent_ == nullptr)
            {
                root = pt_right;
            }
            else if (pt == pt->parent_->left_)
            {
                pt->parent_->left_ = pt_right;
            }
            else
            {
                pt->parent_->right_ = pt_right;
            }

            pt_right->left_ = pt;
            pt->parent_ = pt_right;
        }

        void rotate_right(node_t*& root, node_t*& pt)
        {
            auto pt_left = pt->left_;
            pt->left_ = pt_left->right_;

            if (pt->left_)
            {
                pt->left_->parent_ = pt;
            }

            pt_left->parent_ = pt->parent_;

            if (pt->parent_ == nullptr)
            {
                root = pt_left;
            }
            else if (pt == pt->parent_->left_)
            {
                pt->parent_->left_ = pt_left;
            }
            else
            {
                pt->parent_->right_ = pt_left;
            }

            pt_left->right_ = pt;
            pt->parent_ = pt_left;
        }

        void fix_violation(node_t*& root, node_t*& pt)
        {
            while ((pt != root) && (pt->tag_ != color::black) &&
                (pt->parent_->tag_ == color::red))
            {
                auto parent_pt = pt->parent_;
                auto grand_parent_pt = pt->parent_->parent_;

                /*  Case : A
                    Parent of pt is left child of Grand-parent of pt */
                if (parent_pt == grand_parent_pt->left_)
                {
                    auto uncle_pt = grand_parent_pt->right_;

                    /* Case : 1
                       The uncle of pt is also red
                       Only Recoloring required */
                    if (uncle_pt && uncle_pt->tag_ == color::red)
                    {
                        grand_parent_pt->tag_ = color::red;
                        parent_pt->tag_ = color::black;
                        uncle_pt->tag_ = color::black;
                        pt = grand_parent_pt;
                    }
                    else
                    {
                        /* Case : 2
                           pt is right child of its parent
                           Left-rotation required */
                        if (pt == parent_pt->right_)
                        {
                            rotate_left(root, parent_pt);
                            pt = parent_pt;
                            parent_pt = pt->parent_;
                        }

                        /* Case : 3
                           pt is left child of its parent
                           Right-rotation required */
                        rotate_right(root, grand_parent_pt);
                        std::swap(parent_pt->tag_, grand_parent_pt->tag_);
                        pt = parent_pt;
                    }
                }
                /* Case : B
                   Parent of pt is right child of Grand-parent of pt */
                else
                {
                    auto uncle_pt = grand_parent_pt->left_;

                    /*  Case : 1
                        The uncle of pt is also red
                        Only Recoloring required */
                    if (uncle_pt && uncle_pt->tag_ == color::red)
                    {
                        grand_parent_pt->tag_ = color::red;
                        parent_pt->tag_ = color::black;
                        uncle_pt->tag_ = color::black;
                        pt = grand_parent_pt;
                    }
                    else
                    {
                        /* Case : 2
                           pt is left child of its parent
                           Right-rotation required */
                        if (pt == parent_pt->left_)
                        {
                            rotate_right(root, parent_pt);
                            pt = parent_pt;
                            parent_pt = pt->parent_;
                        }

                        /* Case : 3
                           pt is right child of its parent
                           Left-rotation required */
                        rotate_left(root, grand_parent_pt);
                        std::swap(parent_pt->tag_, grand_parent_pt->tag_);
                        pt = parent_pt;
                    }
                }
            }

            root->tag_ = color::black;
        }
    };
}