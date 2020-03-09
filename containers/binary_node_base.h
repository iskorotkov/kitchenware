#pragma once
#include <functional>
#include <memory>

namespace containers
{
    class binary_node_base
    {
    public:
        using deleter_t = std::function<void(void* const)>;
        using value_t = void;
        using key_t = void;
        using value_ptr = std::unique_ptr<value_t, deleter_t>;
        using key_ptr = std::unique_ptr<key_t, deleter_t>;

        binary_node_base(value_ptr value,
            std::function<key_ptr(const value_ptr&)> comparer,
            deleter_t deleter);

        void value(value_ptr v);
        value_ptr& value() { return value_; }
        void add(value_ptr v);
        void remove(key_ptr key);

        [[nodiscard]] key_ptr key() const;
        [[nodiscard]] const value_ptr& value() const;
        [[nodiscard]] bool exists(const key_ptr&) const;

    private:
        value_ptr value_{};
        std::function<key_ptr(const value_ptr&)> hash_;
        std::unique_ptr<binary_node_base> left_;
        std::unique_ptr<binary_node_base> right_;
        deleter_t deleter_;

        void left_remove(key_ptr k);
        void right_remove(key_ptr k);
        void remove_node();

        [[nodiscard]] bool left_contains(const key_ptr&) const;
        [[nodiscard]] bool right_contains(const key_ptr&) const;
        [[nodiscard]] bool has_children() const;
        [[nodiscard]] bool has_both_children() const;
        [[nodiscard]] bool has_left_child() const;
        [[nodiscard]] bool has_right_child() const;
    };
}
