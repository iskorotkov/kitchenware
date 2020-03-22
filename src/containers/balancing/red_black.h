#pragma once
#include <memory>
#include "declarations.h"
#include "binary_node.h"
#include "value_exists_error.h"

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
            auto key = hash(value);
            auto temp = search(root, key);

            // Item already exists
            if (temp && temp->key() == key)
            {
                throw errors::value_exists_error();
            }

            auto node = new binary_node<TValue, TKey>(value, hash);
            if (root)
            {
                // Root already exists -> new node isn't root
                node->tag_ = color::red;
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
                // There is no root -> new node becomes root
                node->tag_ = color::black;
                root = node;
            }
        }

        void remove(node_t*& root, TKey key)
        {
            if (root == nullptr)
            {
                return;
            }

            auto v = search(root, key);
            if (v->key() == key)
            {
                delete_node(root, v);
            }
        }

    private:
        /// <summary>
        /// Tries to find node with given key.
        /// 
        /// If search is successful, return node with given key.
        /// If not, returns last traversed node.
        /// </summary>
        /// <typeparam name="root">tree root</typeparam>
        /// <typeparam name="key">key to look for</typeparam>
        node_t* search(node_t* root, TKey key)
        {
            auto temp = root;
            decltype(temp) last{};
            while (temp)
            {
                last = temp;
                if (key < temp->key())
                {
                    temp = temp->left_;
                }
                else if (key == temp->key())
                {
                    last = temp;
                    break;
                }
                else
                {
                    temp = temp->right_;
                }
            }
            return last;
        }

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
                : n->parent_->left_;
        }

        /// <summary>
        /// Moves node down and moves another node in its place.
        /// </summary>
        /// <param name="n">node to move down</param>
        /// <param name="n_parent">replacement node</param>
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
            return (n->left_ && n->left_->tag_ == color::red)
                || (n->right_ && n->right_->tag_ == color::red);
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

        /// <summary>
        /// Find leftmost node in given subtree.
        /// </summary>
        /// <param name="x">root of subtree</param>
        /// <returns>leftmost node</returns>
        node_t* successor(node_t* x)
        {
            while (x->left_ != nullptr)
            {
                x = x->left_;
            }
            return x;
        }

        /// <summary>
        /// Find replacement node for node being deleted.
        /// </summary>
        /// <param name="x">node being deleted</param>
        /// <returns>Replacement node</returns>
        node_t* find_replacement(node_t* x)
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
            auto u = find_replacement(v);
            auto uv_black = (u == nullptr || u->tag_ == color::black);
            uv_black &= (v->tag_ == color::black);
            auto parent = v->parent_;

            // Can't replace -> v is a leaf
            if (u == nullptr)
            {
                // v is also a root -> just null the pointer
                if (v == root)
                {
                    root = nullptr;
                }
                // v is leaf, but not root
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

                    // Null pointers to this leaf
                    if (is_on_left(v))
                    {
                        parent->left_ = nullptr;
                    }
                    else
                    {
                        parent->right_ = nullptr;
                    }
                }

                // v is already a leaf
                delete v;
                return;
            }

            // v has exactly one descendant
            if (v->left_ == nullptr || v->right_ == nullptr)
            {
                if (v == root)
                {
                    // Make u a root node
                    root = u;
                    // Assign pointers of u and null everything in v
                    replace_node(v, u);
                    delete v;
                }
                else
                {
                    // Replace v with u
                    if (is_on_left(v))
                    {
                        parent->left_ = u;
                    }
                    else
                    {
                        parent->right_ = u;
                    }

                    // Delete v
                    v->left_ = nullptr;
                    v->right_ = nullptr;
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

            if (root == v)
            {
                root = u;
            }
            swap_with_child(v, u);

            // Recursive call
            delete_node(root, v);
        }

        /// <summary>
        /// Replaces given node with replacement node
        /// and nulls all pointers on given node.
        /// </summary>
        /// <param name="node">node to be replaced</param>
        /// <param name="replacement">replacement node</param>
        void replace_node(node_t* node, node_t* replacement)
        {
            // Replacement isn't left adjacent node
            if (replacement != node->left_)
            {
                replacement->left_ = node->left_;
                if (node->left_)
                {
                    node->left_->parent_ = replacement;
                }
            }

            // Replacement isn't right adjacent node
            if (replacement != node->right_)
            {
                replacement->right_ = node->right_;
                if (node->right_)
                {
                    node->right_->parent_ = replacement;
                }
            }

            // Parent nodes
            replacement->parent_ = node->parent_;
            if (auto parent = node->parent_)
            {
                if (parent->left_ == node)
                {
                    parent->left_ = replacement;
                }
                else
                {
                    parent->right_ = replacement;
                }
            }

            replacement->tag_ = node->tag_;

            node->parent_ = nullptr;
            node->left_ = nullptr;
            node->right_ = nullptr;
        }

        void swap_with_child(node_t* node, node_t* replacement)
        {
            auto left = replacement->left_;
            auto right = replacement->right_;

            // Save pointer to parent of replacement node
            node_t* parent{};
            if (replacement->parent_ == node)
            {
                // Nodes are adjacent -> point to new parent
                parent = replacement;
            }
            else
            {
                // Nodes are distant
                parent = replacement->parent_;
            }

            // Set parent node pointers
            if (node->parent_)
            {
                if (node == node->parent_->left_)
                {
                    node->parent_->left_ = replacement;
                }
                else
                {
                    node->parent_->right_ = replacement;
                }
            }

            // Set left/right pointers
            if (replacement == node->left_)
            {
                // Replacement is left child
                replacement->left_ = node;
                replacement->right_ = node->right_;
                if (node->right_)
                {
                    node->right_->parent_ = replacement;
                }
            }
            else if (replacement == node->right_)
            {
                // Replacement if right child
                replacement->left_ = node->left_;
                replacement->right_ = node;
                if (node->left_)
                {
                    node->left_->parent_ = replacement;
                }
            }
            else
            {
                replacement->left_ = node->left_;
                replacement->right_ = node->right_;
                if (node->left_)
                {
                    node->left_->parent_ = replacement;
                }
                if (node->right_)
                {
                    node->right_->parent_ = replacement;
                }
            }

            std::swap(node->tag_, replacement->tag_);

            replacement->parent_ = node->parent_;

            // Set pointers to node that being deleted
            if (left)
            {
                left->parent_ = node;
            }
            if (right)
            {
                right->parent_ = node;
            }
            if (parent)
            {
                if (parent->left_ == replacement)
                {
                    parent->left_ = node;
                }
                else
                {
                    parent->right_ = node;
                }
            }
            node->parent_ = parent;
            node->left_ = left;
            node->right_ = right;
        }

        void fix_double_black(node_t*& root, node_t* x)
        {
            if (x == root)
            {
                return;
            }

            auto sib = sibling(x);
            auto parent = x->parent_;

            if (sib == nullptr)
            {
                // Push problem up
                // Recursive call
                fix_double_black(root, parent);
            }
            else
            {
                if (sib->tag_ == color::red)
                {
                    parent->tag_ = color::red;
                    sib->tag_ = color::black;
                    if (is_on_left(sib))
                    {
                        right_rotate(root, parent);
                    }
                    else
                    {
                        left_rotate(root, parent);
                    }
                    // Recursive call
                    fix_double_black(root, x);
                }
                else
                {
                    // Sibling is black
                    if (has_red_child(sib))
                    {
                        if (sib->left_
                            && sib->left_->tag_ == color::red)
                        {
                            // Left sibling child is red
                            if (is_on_left(sib))
                            {
                                sib->left_->tag_ = sib->tag_;
                                sib->tag_ = parent->tag_;
                                right_rotate(root, parent);
                            }
                            else
                            {
                                sib->left_->tag_ = parent->tag_;
                                right_rotate(root, sib);
                                left_rotate(root, parent);
                            }
                        }
                        else
                        {
                            // Right sibling child is red
                            if (is_on_left(sib))
                            {
                                sib->right_->tag_ = parent->tag_;
                                left_rotate(root, sib);
                                right_rotate(root, parent);
                            }
                            else
                            {
                                sib->right_->tag_ = sib->tag_;
                                sib->tag_ = parent->tag_;
                                left_rotate(root, parent);
                            }
                        }
                        parent->tag_ = color::black;
                    }
                    else
                    {
                        // Both children are black
                        sib->tag_ = color::red;
                        if (parent->tag_ == color::black)
                        {
                            // Recursive call
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