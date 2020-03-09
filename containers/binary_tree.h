#pragma once
#include <memory>
#include <functional>
#include "binary_tree_base.h"

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_tree final : public binary_tree_base
    {
    public:
        binary_tree() :
            binary_tree_base([](auto value) { return value; },
                [](auto value) { delete (TValue*)value; })
        {
        }

        explicit binary_tree(std::function<TKey(const TValue&)> comparer) :
            binary_tree_base(comparer, [](auto value) { delete (TValue*)value; })
        {
        }

        void add(TValue value) { binary_tree_base.add(value); }
        void remove(TKey key) { binary_tree_base.remove(key); }
        [[nodiscard]] bool exists(TKey key) const { return binary_tree_base.exists(key); }
    };
}
