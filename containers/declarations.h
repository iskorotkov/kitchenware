#pragma once

namespace containers
{
    template <typename TValue, typename TKey>
    class binary_tree;

    template <typename TValue, typename TKey>
    class binary_node;

    namespace balancing
    {
        template <typename TValue, typename TKey>
        class red_black;
    }

    namespace views
    {
        template <typename TValue, typename TKey>
        class prefix_view;

        template <typename TValue, typename TKey>
        class postfix_view;

        template <typename TValue, typename TKey>
        class infix_view;
    }
}
