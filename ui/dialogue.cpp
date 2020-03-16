#include <iostream>
#include "dialogue.h"
#include "prefix_view.h"
#include "infix_view.h"
#include "postfix_view.h"
#include "electric_stove.h"
#include "gas_stove.h"
#include "saucepan.h"
#include "slow_cooker.h"
#include "stove.h"
#include "kitchenware.h"

ui::dialogue::dialogue() :
    tree_([](auto& value) { return value.number(); })
{
}

void ui::dialogue::start()
{
    while (true)
    {
        list_all_options();
        std::cout << "\n";
        select_option();
        std::cout << "\n";
    }
}

void ui::dialogue::list_all_options()
{
    std::cout << "Select option from list:\n" << "[1] add new item\n"
        << "[2] remove item\n" << "[3] check if exists\n"
        << "[4] list in prefix order\n" << "[5] list in infix order\n"
        << "[6] list in postfix order\n";
}

void ui::dialogue::select_option()
{
    int option;
    std::cin >> option;
    switch (option)
    {
    case 1:
        add_new_item();
        break;
    case 2:
        remove_item();
        break;
    case 3:
        check_if_exists();
        break;
    case 4:
        //for (const auto& iter : tree_.create_prefix_view())
        //{
        //    iter->print(std::cout);
        //}
        break;
    case 5:
        for (const auto& iter : tree_.create_infix_view())
        {
            iter->print(std::cout);
            std::cout << "\n";
        }
        break;
    case 6:
        //for (const auto& iter : tree_.create_postfix_view())
        //{
        //    iter->print(std::cout);
        //}
        break;
    default:
        break;
    }
}

void ui::dialogue::add_new_item()
{
    std::cout << "\nSelect type from list:\n" << "[1] electric stove\n"
        << "[2] gas_stove\n" << "[3] saucepan\n" << "[4] slow cooker\n"
        << "[5] stove\n";
    int type;
    std::cin >> type;
    kitchen::kitchenware* kw;
    switch (type)
    {
    case 1:
        kw = new kitchen::electric_stove();
        break;
    case 2:
        kw = new kitchen::gas_stove();
        break;
    case 3:
        kw = new kitchen::saucepan();
        break;
    case 4:
        kw = new kitchen::slow_cooker();
        break;
    case 5:
        kw = new kitchen::stove();
        break;
    default:
        break;
    }

    int i;
    double d;
    std::string s;
    bool b;

    std::cout << "Id: ";
    std::cin >> i;
    kw->number(i);

    if (auto es = dynamic_cast<kitchen::electric_stove*>(kw))
    {
        std::cout << "Power: ";
        std::cin >> i;
        es->power(i);
    }

    if (auto gs = dynamic_cast<kitchen::gas_stove*>(kw))
    {
        std::cout << "Gas waste: ";
        std::cin >> i;
        gs->gas_waste(i);
    }

    if (auto sp = dynamic_cast<kitchen::saucepan*>(kw))
    {
        std::cout << "Volume: ";
        std::cin >> d;
        sp->volume(d);
    }

    if (auto sc = dynamic_cast<kitchen::slow_cooker*>(kw))
    {
        std::cout << "Is pressure cooker (0, 1): ";
        std::cin >> b;
        sc->volume(b);
    }

    if (auto st = dynamic_cast<kitchen::stove*>(kw))
    {
        std::cout << "Color (RGB, 0-255, separated by space): ";
        int color_r, color_g, color_b;
        std::cin >> color_r >> color_g >> color_b;
        st->color({ color_r, color_g, color_b });
    }

    tree_.add(kw);
}

void ui::dialogue::remove_item()
{
    std::cout << "\nId: ";
    int id;
    std::cin >> id;
    tree_.remove(id);
}

void ui::dialogue::check_if_exists()
{
    std::cout << "\nId: ";
    int id;
    std::cin >> id;
    std::cout << tree_.exists(id) << "\n";
}
