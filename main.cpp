#include <iostream>
#include "containers/binary_tree.h"

int main()
{
    containers::binary_tree<int> tree;
    tree.add(5);
    tree.add(4);
    tree.add(6);

    auto view = tree.create_prefix_view();
    for (auto it = view.cbegin();
         it < view.cend();
         ++it)
    {
        std::cout << *it;
    }
}
