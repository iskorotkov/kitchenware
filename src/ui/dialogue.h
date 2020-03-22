#pragma once
#include "poly_tree.h"
#include "kitchenware.h"

namespace kitchen
{
    class electric_stove;
    class gas_stove;
    class saucepan;
    class slow_cooker;
    class stove;
}

namespace ui
{
    class dialogue
    {
    public:
        dialogue();

        void start();

    private:
        containers::poly_tree<kitchen::kitchenware, int> tree_;

        void list_all_options();
        void select_option();
        void add_new_item();
        std::unique_ptr<kitchen::kitchenware> create_kitchenware(int type, int id);
        void set_values(kitchen::kitchenware* kw);
        void set_power(kitchen::electric_stove* es);
        void set_gas_waste(kitchen::gas_stove* gs);
        void set_volume(kitchen::saucepan* sp);
        void set_is_pressure_cooker(kitchen::slow_cooker* sc);
        void set_color(kitchen::stove* st);
        void remove_item();
        void check_if_exists();
    };
}
