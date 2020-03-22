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
    class poly_tree : public binary_tree<std::unique_ptr<TValue>, TKey>
    {
        friend class views::infix_view<TValue, TKey>;
        friend class views::prefix_view<TValue, TKey>;
        friend class views::postfix_view<TValue, TKey>;

    public:
        poly_tree(std::function<TKey(const TValue&)> hash);

        void add(TValue* value);

        [[nodiscard]] auto create_prefix_view() const { return create_prefix_view(); }
        // [[nodiscard]] auto create_infix_view() const { return tree_.create_infix_view(); }
        // [[nodiscard]] auto create_postfix_view() const { return tree_.create_postfix_view(); };
    };

    template<typename TValue, typename TKey>
    inline poly_tree<TValue, TKey>::poly_tree(std::function<TKey(const TValue&)> hash)
        : binary_tree<std::unique_ptr<TValue>, TKey>([hash](const auto& ptr) { return hash(*ptr); })
    {
    }

    template<typename TValue, typename TKey>
    inline void poly_tree<TValue, TKey>::add(TValue* value)
    {
        binary_tree<std::unique_ptr<TValue>, TKey>::add(std::unique_ptr<TValue>(value));
    }
}
