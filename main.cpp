#include <iostream>
#include "containers/binary_tree.h"

int main()
{
    containers::binary_tree<int> tree;
    tree.add(5);
    tree.add(4);
    tree.add(6);

    std::cout << tree.exists(6) << tree.exists(8);
}
