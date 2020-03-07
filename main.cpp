#include <iostream>
#include "binary_tree.h"

int main()
{
    containers::binary_tree<int, int> tree;
    tree.add(5);
    tree.add(4);
    tree.add(1);
    tree.add(6);
    tree.add(8);
    tree.add(7);
    tree.add(9);
    tree.add(11);
    tree.add(10);

    for (auto it : tree.create_prefix_view())
    {
        std::cout << it << " ";
    }

    std::cout << "\n";

    for (auto it : tree.create_postfix_view())
    {
        std::cout << it << " ";
    }

    std::cout << "\n";

    for (auto it : tree.create_infix_view())
    {
        std::cout << it << " ";
    }
}
