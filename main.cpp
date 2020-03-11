#include <iostream>
#include "poly_tree.h"
#include "slow_cooker.h"

using namespace containers;
using namespace kitchen;

int main()
{
    //poly_tree<kitchenware, int> tree([](auto& k)
    //    {
    //        return k.number();
    //    });

    binary_tree<int, int> tree;
    tree.add(1);
    tree.add(200);
    tree.add(60);

    //auto c = new slow_cooker();
    //c->power(1);
    //c->color({ 1,2,3 });
    //c->print(std::cout);
    //tree.add(c);

    //auto b = tree.create_prefix_view().begin();
    //std::cout << b.level() << std::endl;

    for (const auto& it : tree.create_prefix_view())
    {
        //it->print(std::cout);
        std::cout << it << " ";
    }

    std::cout << "\n";

    for (const auto& it : tree.create_postfix_view())
    {
        std::cout << it << " ";
    }

    std::cout << "\n";

    for (const auto& it : tree.create_infix_view())
    {
        std::cout << it << " ";
    }
}
