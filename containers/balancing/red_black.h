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
            black = 0,
            red = 1
        };

        void add(node_t*& root, TValue& value, std::function<TKey(const TValue&)> hash)
        {
            //auto node = new binary_node<TValue, TKey>(value, hash_);
            //root_ = balancer_.insert(root_, node);
            //balancer_.fix_violation(root_, node);

            auto key = hash(value);
            auto temp = search(root, key);
            if (temp && temp->key() == key)
            {
                // TODO: value already exists
                return;
            }

            auto node = new binary_node<TValue, TKey>(value, hash);
            if (root)
            {
                node->parent_ = temp;
                if (key < temp->key())
                {
                    temp->left_ = node;
                }
                else
                {
                    temp->right_ = node;
                }
                fix_red_red(root, node);
            }
            else
            {
                root = node;
            }
        }

        void remove(node_t*& root, TKey key)
        {
            if (root == nullptr)
            {
                return;
            }

            auto v = search(key);
            if (v->key() == key)
            {
                delete_node(root, v);
            }
        }

        node_t* search(node_t* root, TKey key)
        {
            auto temp = root;
            while (temp)
            {
                if (key < temp->key())
                {
                    if (temp->left_ == nullptr)
                    {
                        break;
                    }
                    else
                    {
                        temp = temp->left_;
                    }
                }
                else if (key == temp->key())
                {
                    break;
                }
                else
                {
                    if (temp->right_ == nullptr)
                    {
                        break;
                    }
                    else
                    {
                        temp = temp->right_;
                    }
                }
            }
            return temp;
        }

        //node_t* insert(node_t* root, node_t* pt)
        //{
        //    if (root == nullptr)
        //    {
        //        return pt;
        //    }

        //    if (pt->key() < root->key())
        //    {
        //        root->left_ = insert(root->left_, pt);
        //        root->left_->parent_ = root;
        //    }
        //    else if (pt->key() > root->key())
        //    {
        //        root->right_ = insert(root->right_, pt);
        //        root->right_->parent_ = root;
        //    }

        //    return root;
        //}

        //void rotate_left(node_t*& root, node_t*& pt)
        //{
        //    auto pt_right = pt->right_;
        //    pt->right_ = pt_right->left_;

        //    if (pt->right_)
        //    {
        //        pt->right_->parent_ = pt;
        //    }

        //    pt_right->parent_ = pt->parent_;

        //    if (pt->parent_ == nullptr)
        //    {
        //        root = pt_right;
        //    }
        //    else if (pt == pt->parent_->left_)
        //    {
        //        pt->parent_->left_ = pt_right;
        //    }
        //    else
        //    {
        //        pt->parent_->right_ = pt_right;
        //    }

        //    pt_right->left_ = pt;
        //    pt->parent_ = pt_right;
        //}

        //void rotate_right(node_t*& root, node_t*& pt)
        //{
        //    auto pt_left = pt->left_;
        //    pt->left_ = pt_left->right_;

        //    if (pt->left_)
        //    {
        //        pt->left_->parent_ = pt;
        //    }

        //    pt_left->parent_ = pt->parent_;

        //    if (pt->parent_ == nullptr)
        //    {
        //        root = pt_left;
        //    }
        //    else if (pt == pt->parent_->left_)
        //    {
        //        pt->parent_->left_ = pt_left;
        //    }
        //    else
        //    {
        //        pt->parent_->right_ = pt_left;
        //    }

        //    pt_left->right_ = pt;
        //    pt->parent_ = pt_left;
        //}

        //void fix_violation(node_t*& root, node_t*& pt)
        //{
        //    while ((pt != root) && (pt->tag_ != color::black) &&
        //        (pt->parent_->tag_ == color::red))
        //    {
        //        auto parent_pt = pt->parent_;
        //        auto grand_parent_pt = pt->parent_->parent_;

        //        /*  Case : A
        //            Parent of pt is left child of Grand-parent of pt */
        //        if (parent_pt == grand_parent_pt->left_)
        //        {
        //            auto uncle_pt = grand_parent_pt->right_;

        //            /* Case : 1
        //               The uncle of pt is also red
        //               Only Recoloring required */
        //            if (uncle_pt && uncle_pt->tag_ == color::red)
        //            {
        //                grand_parent_pt->tag_ = color::red;
        //                parent_pt->tag_ = color::black;
        //                uncle_pt->tag_ = color::black;
        //                pt = grand_parent_pt;
        //            }
        //            else
        //            {
        //                /* Case : 2
        //                   pt is right child of its parent
        //                   Left-rotation required */
        //                if (pt == parent_pt->right_)
        //                {
        //                    rotate_left(root, parent_pt);
        //                    pt = parent_pt;
        //                    parent_pt = pt->parent_;
        //                }

        //                /* Case : 3
        //                   pt is left child of its parent
        //                   Right-rotation required */
        //                rotate_right(root, grand_parent_pt);
        //                std::swap(parent_pt->tag_, grand_parent_pt->tag_);
        //                pt = parent_pt;
        //            }
        //        }
        //        /* Case : B
        //           Parent of pt is right child of Grand-parent of pt */
        //        else
        //        {
        //            auto uncle_pt = grand_parent_pt->left_;

        //            /*  Case : 1
        //                The uncle of pt is also red
        //                Only Recoloring required */
        //            if (uncle_pt && uncle_pt->tag_ == color::red)
        //            {
        //                grand_parent_pt->tag_ = color::red;
        //                parent_pt->tag_ = color::black;
        //                uncle_pt->tag_ = color::black;
        //                pt = grand_parent_pt;
        //            }
        //            else
        //            {
        //                /* Case : 2
        //                   pt is left child of its parent
        //                   Right-rotation required */
        //                if (pt == parent_pt->left_)
        //                {
        //                    rotate_right(root, parent_pt);
        //                    pt = parent_pt;
        //                    parent_pt = pt->parent_;
        //                }

        //                /* Case : 3
        //                   pt is right child of its parent
        //                   Left-rotation required */
        //                rotate_left(root, grand_parent_pt);
        //                std::swap(parent_pt->tag_, grand_parent_pt->tag_);
        //                pt = parent_pt;
        //            }
        //        }
        //    }

        //    root->tag_ = color::black;
        //}

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

        bool is_on_left(node_t* n)
        {
            return n == n->parent_->left_;
        }

        node_t* sibling(node_t* n)
        {
            if (n->parent_ == nullptr)
            {
                return nullptr;
            }
            return is_on_left(n)
                ? n->parent_->right_
                : n->parent->left_;
        }

        void move_down(node_t* n, node_t* n_parent)
        {
            if (n->parent_)
            {
                if (is_on_left(n))
                {
                    n->parent_->left_ = n_parent;
                }
                else
                {
                    n->parent_->right_ = n_parent;
                }
            }
            n_parent->parent_ = n->parent_;
            n->parent_ = n_parent;
        }

        bool has_red_child(node_t* n)
        {
            return n->left_ && n->left_->tag_ == color::red
                || n->right_ && n->right_->tag_ == color::red;
        }

        void left_rotate(node_t*& root, node_t* n)
        {
            auto n_parent = n->right_;

            if (n == root)
            {
                root = n_parent;
            }

            move_down(n, n_parent);
            n->right_ = n_parent->left_;

            if (n_parent->left_)
            {
                n_parent->left_->parent_ = n;
            }
            n_parent->left_ = n;
        }

        void right_rotate(node_t*& root, node_t* n)
        {
            auto n_parent = n->left_;

            if (n == root)
            {
                root = n_parent;
            }

            move_down(n, n_parent);
            n->left_ = n_parent->right_;

            if (n_parent->right_)
            {
                n_parent->right_->parent_ = n;
            }
            n_parent->right_ = n;
        }

        void fix_red_red(node_t*& root, node_t* x)
        {
            // if x is root color it black and return 
            if (x == root)
            {
                x->tag_ = color::black;
                return;
            }

            // initialize parent, grandparent, uncle 
            auto parent = x->parent_;
            auto grand = grandparent(x);
            auto un = uncle(x);

            if (parent->tag_ != color::black)
            {
                if (un && un->tag_ == color::red)
                {
                    // uncle red, perform recoloring and recurse 
                    parent->tag_ = color::black;
                    un->tag_ = color::black;
                    grand->tag_ = color::red;
                    fix_red_red(root, grand);
                }
                else
                {
                    // Else perform LR, LL, RL, RR 
                    if (is_on_left(parent))
                    {
                        if (is_on_left(x))
                        {
                            // for left right 
                            std::swap(parent->tag_, grand->tag_);
                        }
                        else
                        {
                            left_rotate(root, parent);
                            std::swap(x->tag_, grand->tag_);
                        }
                        // for left left and left right 
                        right_rotate(root, grand);
                    }
                    else
                    {
                        if (is_on_left(x))
                        {
                            // for right left 
                            right_rotate(root, parent);
                            std::swap(x->tag_, grand->tag_);
                        }
                        else
                        {
                            std::swap(parent->tag_, grand->tag_);
                        }

                        // for right right and right left 
                        left_rotate(root, grand);
                    }
                }
            }
        }

        node_t* successor(node_t* x)
        {
            while (x->left_ != nullptr)
            {
                x = x->left_;
            }
            return x;
        }

        node_t* replace(node_t* x)
        {
            if (x->left_ && x->right_)
            {
                return successor(x->right_);
            }

            if (x->left_ == nullptr && x->right_ == nullptr)
            {
                return nullptr;
            }

            return x->left_ ? x->left_ : x->right_;
        }

        void delete_node(node_t*& root, node_t* v)
        {
            auto u = replace(v);
            auto uv_black = (u == nullptr || u->tag_ == color::black);
            uv_black &= (v->tag_ == color::black);
            auto parent = v->parent_;

            if (u)
            {
                if (v == root)
                {
                    root = nullptr;
                }
                else
                {
                    if (uv_black)
                    {
                        fix_double_black(root, v);
                    }
                    else
                    {
                        if (auto s = sibling(v))
                        {
                            s->tag_ = color::red;
                        }
                    }

                    if (is_on_left(v))
                    {
                        parent->left_ = nullptr;
                    }
                    else
                    {
                        parent->right_ = nullptr;
                    }
                }
                delete v;
                return;
            }

            if (v->left_ == nullptr || v->right_ == nullptr)
            {
                if (v == root)
                {
                    u->left_ = v->left_;
                    u->right_ = v->right_;
                    if (v->left_)
                    {
                        v->left_->parent_ = u;
                        v->left_ == nullptr;
                    }
                    if (v->right_)
                    {
                        v->right_->parent_ = u;
                        v->right_->nullptr;
                    }
                    delete v;
                }
                else
                {
                    if (is_on_left(v))
                    {
                        parent->left_ = u;
                    }
                    else
                    {
                        parent->right_ = u;
                    }
                    delete v;
                    u->parent_ = parent;
                    if (uv_black)
                    {
                        fix_double_black(root, u);
                    }
                    else
                    {
                        u->tag_ = color::black;
                    }
                }
                return;
            }

            swap_nodes(u, v);
            delete_node(root, u);
        }

        void swap_nodes(node_t* u, node_t* v)
        {
            if (u->left_)
            {
                u->left_->parent_ = v;
            }
            if (u->right_)
            {
                u->right_->parent_ = v;
            }
            if (v->left_)
            {
                v->left_->parent_ = u;
            }
            if (v->right_)
            {
                v->right_->parent_ = u;
            }
            std::swap(u->parent_, v->parent_);
            std::swap(u->left_, v->left_);
            std::swap(u->right_, v->right_);
        }

        void fix_double_black(node_t*&, node_t* x)
        {
            if (x == root)
            {
                return;
            }

            auto sibling = sibling(x);
            auto parent = x->parent_;

            if (sibling == nullptr)
            {
                fix_double_black(root, parent);
            }
            else
            {
                if (sibling->tag_ == color::red)
                {
                    parent->tag_ = color::red;
                    sibling->tag_ = color::black;
                    if (is_on_left(sibling))
                    {
                        right_rotate(root, parent);
                    }
                    else
                    {
                        left_rotate(root, parent);
                    }
                    fix_double_black(root, x);
                }
                else
                {
                    if (has_red_child(sibling))
                    {
                        if (sibling->left_
                            && sibling->left_->tag_ == color::red)
                        {
                            if (is_on_left(sibling))
                            {
                                sibling->left_->tag_ = sibling->tag_;
                                sibling->tag_ = parent->tag_;
                                right_rotate(root, parent);
                            }
                            else
                            {
                                sibling->left_->tag_ = parent->tag_;
                                right_rotate(root, sibling);
                                left_rotate(parent);
                            }
                        }
                        else
                        {
                            if (is_on_left(sibling))
                            {
                                sibling->right_->tag_ = parent->tag_;
                                left_rotate(root, sibling);
                                right_rotate(root, parent);
                            }
                            else
                            {
                                sibling->right_->tag_ = sibling->tag_;
                                sibling->tag_ = parent->tag_;
                                left_rotate(root, parent);
                            }
                        }
                        parent->tag_ = color::black;
                    }
                    else
                    {
                        sibling->tag_ = color::red;
                        if (parent->tag_ == color::black)
                        {
                            fix_double_black(root, parent);
                        }
                        else
                        {
                            parent->tag_ = color::black;
                        }
                    }
                }
            }
        }
    };
}