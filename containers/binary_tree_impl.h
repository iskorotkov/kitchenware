#pragma once
#include <memory>
#include <functional>

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_tree final
    {
        friend class views::prefix_view<TValue, TKey>;
        friend class views::postfix_view<TValue, TKey>;
        friend class views::infix_view<TValue, TKey>;

    public:
        binary_tree() : hash_([](auto value) { return value; })
        {
        }

        explicit binary_tree(std::function<TKey(TValue)> comparer) : hash_(comparer)
        {
        }

        void add(TValue value);
        void remove(TKey key);
        [[nodiscard]] bool exists(TKey key) const;

        [[nodiscard]] auto create_prefix_view() const { return views::prefix_view<TValue, TKey>(this); }
        [[nodiscard]] auto create_infix_view() const { return views::infix_view<TValue, TKey>(this); }
        [[nodiscard]] auto create_postfix_view() const { return views::postfix_view<TValue, TKey>(this); };

    private:
        std::unique_ptr<binary_node<TValue, TKey>> root_;
        std::function<TKey(const TValue&)> hash_;
    };
}

template <typename TValue, typename TKey>
void containers::binary_tree<TValue, TKey>::remove(TKey key)
{
    if (auto root = root_.get())
    {
        root->remove(value);
    }
}

template <typename TValue, typename TKey>
bool containers::binary_tree<TValue, TKey>::exists(TKey key) const
{
    if (const auto root = root_.get())
    {
        return root->exists(value);
    }
    return false;
}

template <typename TValue, typename TKey>
void containers::binary_tree<TValue, TKey>::add(TValue value)
{
    if (auto root = root_.get())
    {
        root->add(value);
    }
    else
    {
        root_ = std::make_unique<binary_node<TValue, TKey>>(value, hash_);
    }
}
