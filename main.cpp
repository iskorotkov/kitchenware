#include <iostream>
#include "binary_tree.h"

int main()
{
    containers::binary_tree<std::string, int> tree([](auto i) { return i.size(); });
    tree.add("asad");
    tree.add("b");
    tree.add("csd");
    tree.add("d");
    tree.add("eds");

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
