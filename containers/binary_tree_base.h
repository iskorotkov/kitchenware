#pragma once
#include <memory>
#include <functional>
#include "binary_node_base.h"

namespace containers
{
    class binary_tree_base
    {
    public:
        using deleter_t = std::function<void(void* const)>;
        using value_t = void;
        using key_t = void;
        using value_ptr = std::unique_ptr<value_t, deleter_t>;
        using key_ptr = std::unique_ptr<key_t, deleter_t>;

        binary_tree_base(std::function<key_ptr(const value_ptr&)> comparer,
            deleter_t deleter);

        void add(value_ptr value);
        void remove(key_ptr key);

        [[nodiscard]] bool exists(key_ptr key) const;

    private:
        std::unique_ptr<binary_node_base> root_;
        std::function<key_ptr(const value_ptr&)> hash_;
        deleter_t deleter_;
    };
}
