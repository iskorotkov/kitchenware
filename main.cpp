#include <iostream>
#include "binary_tree.h"

int main()
{
    containers::binary_tree<int> tree;
    tree.add(5);
    tree.add(4);
    tree.add(6);
    tree.add(8);
    tree.add(1);
    tree.add(7);
    tree.add(9);
    tree.add(11);
    tree.add(10);

    auto view = tree.create_prefix_view();
    for (auto it = view.begin();
         it < view.end();
         ++it)
    {
        std::cout << "level: " << it.level() << " , value: " << it.value() << "\n";
    }

    std::cout << std::endl;

    for (auto it : view)
    {
        std::cout << it << " ";
        //std::cout << "level: " << it.level() << " , value: " << it.value() << "\n";
    }
}
