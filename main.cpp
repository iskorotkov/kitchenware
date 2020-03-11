#include <iostream>
#include "binary_tree.h"
#include "slow_cooker.h"

using namespace containers;
using namespace kitchen;

int main()
{
    containers::binary_tree<kitchenware, int> tree([](auto& k)
        {
            return k.number();
        });

    slow_cooker c;
    c.power(1);
    c.color({ 1,2,3 });
    c.print(std::cout);
    //tree.add(c);

    for (const auto& it : tree.create_prefix_view())
    {
        it.print(std::cout);
        //std::cout << it << " ";
    }

    std::cout << "\n";

    for (const auto& it : tree.create_postfix_view())
    {
        //std::cout << it << " ";
    }

    std::cout << "\n";

    for (const auto& it : tree.create_infix_view())
    {
        //std::cout << it << " ";
    }
}
