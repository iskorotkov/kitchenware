#include "dialogue.h"
#include "dialogue.h"
#include "dialogue.h"
#include "dialogue.h"
#include "dialogue.h"
#include "dialogue.h"
#include "dialogue.h"
#include <iostream>
#include <memory>
#include "dialogue.h"
#include "infix_view.h"
#include "prefix_view.h"
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
    using namespace containers::views;
    using namespace kitchen;

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
        prefix_view<std::unique_ptr<kitchenware>, int>::traverse(tree_,
            [](const auto& kw)
            {
                kw->print(std::cout);
                std::cout << "\n";
            });
        break;
    case 5:
        infix_view<std::unique_ptr<kitchenware>, int>::traverse(tree_,
            [](const auto& kw)
            {
                kw->print(std::cout);
                std::cout << "\n";
            });
        break;
    case 6:
        postfix_view<std::unique_ptr<kitchenware>, int>::traverse(tree_,
            [](const auto& kw)
            {
                kw->print(std::cout);
                std::cout << "\n";
            });
        break;
    default:
        break;
    }
}

void ui::dialogue::add_new_item()
{
    std::cout << "\nSelect type from list:\n" << "[1] electric stove\n"
        << "[2] gas stove\n" << "[3] saucepan\n" << "[4] slow cooker\n"
        << "[5] stove\n";
    int type;
    std::cin >> type;

    std::cout << "Id: ";
    int id;
    std::cin >> id;
    if (tree_.exists(id))
    {
        std::cout << "\nThis item already exists\n";
        return;
    }

    std::unique_ptr<kitchen::kitchenware> kw = create_kitchenware(type, id);
    set_values(kw.get());
    tree_.add(kw.release());
}

std::unique_ptr<kitchen::kitchenware> ui::dialogue::create_kitchenware(int type, int id)
{
    std::unique_ptr<kitchen::kitchenware> kw;
    switch (type)
    {
    case 1:
        kw = std::make_unique<kitchen::electric_stove>();
        break;
    case 2:
        kw = std::make_unique<kitchen::gas_stove>();
        break;
    case 3:
        kw = std::make_unique<kitchen::saucepan>();
        break;
    case 4:
        kw = std::make_unique<kitchen::slow_cooker>();
        break;
    case 5:
        kw = std::make_unique<kitchen::stove>();
        break;
    default:
        break;
    }
    kw->number(id);
    return kw;
}

void ui::dialogue::set_values(kitchen::kitchenware* kw)
{
    if (auto es = dynamic_cast<kitchen::electric_stove*>(kw))
    {
        set_power(es);
    }

    if (auto gs = dynamic_cast<kitchen::gas_stove*>(kw))
    {
        set_gas_waste(gs);
    }

    if (auto sp = dynamic_cast<kitchen::saucepan*>(kw))
    {
        set_volume(sp);
    }

    if (auto sc = dynamic_cast<kitchen::slow_cooker*>(kw))
    {
        set_is_pressure_cooker(sc);
    }

    if (auto st = dynamic_cast<kitchen::stove*>(kw))
    {
        set_color(st);
    }
}

void ui::dialogue::set_power(kitchen::electric_stove* es)
{
    std::cout << "Power: ";
    int power;
    std::cin >> power;
    es->power(power);
}

void ui::dialogue::set_gas_waste(kitchen::gas_stove* gs)
{
    std::cout << "Gas waste: ";
    int gas;
    std::cin >> gas;
    gs->gas_waste(gas);
}

void ui::dialogue::set_volume(kitchen::saucepan* sp)
{
    std::cout << "Volume: ";
    double volume;
    std::cin >> volume;
    sp->volume(volume);
}

void ui::dialogue::set_is_pressure_cooker(kitchen::slow_cooker* sc)
{
    std::cout << "Is pressure cooker (0, 1): ";
    bool is_pressure_cooker;
    std::cin >> is_pressure_cooker;
    sc->is_pressure_cooker(is_pressure_cooker);
}

void ui::dialogue::set_color(kitchen::stove* st)
{
    std::cout << "Color (RGB, 0-255, separated by space): ";
    int red, green, blue;
    std::cin >> red >> green >> blue;
    st->color({ red, green, blue });
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
    std::cout << (tree_.exists(id) ? "exists" : "not exists") << "\n";
}
