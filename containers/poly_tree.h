#pragma once
#include <memory>
#include "declarations.h"
#include "prefix_view.h"
#include "postfix_view.h"
#include "infix_view.h"
#include "binary_tree.h"

namespace containers
{
    template <typename TValue, typename TKey>
    class poly_tree
    {
    public:
        poly_tree(std::function<TKey(const TValue&)> hash);

        void add(TValue* value);
        void remove(TKey key);

        [[nodiscard]] bool exists(TKey key) const;
        [[nodiscard]] auto create_prefix_view() const { return tree_.create_prefix_view(); }
        [[nodiscard]] auto create_infix_view() const { return tree_.create_infix_view(); }
        [[nodiscard]] auto create_postfix_view() const { return tree_.create_postfix_view(); };

    private:
        binary_tree<std::unique_ptr<TValue>, TKey> tree_;
    };

    template<typename TValue, typename TKey>
    inline poly_tree<TValue, TKey>::poly_tree(std::function<TKey(const TValue&)> hash)
        : tree_([hash](const auto& ptr) { return hash(*ptr); })
    {
    }

    template<typename TValue, typename TKey>
    inline void poly_tree<TValue, TKey>::add(TValue* value)
    {
        tree_.add(std::unique_ptr<TValue>(value));
    }

    template<typename TValue, typename TKey>
    inline void poly_tree<TValue, TKey>::remove(TKey key)
    {
        tree_.remove(key);
    }

    template<typename TValue, typename TKey>
    inline bool poly_tree<TValue, TKey>::exists(TKey key) const
    {
        return tree_.exists(key);
    }
}
