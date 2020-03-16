#pragma once
#include "poly_tree.h"
#include "kitchenware.h"

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
        void remove_item();
        void check_if_exists();
    };
}
