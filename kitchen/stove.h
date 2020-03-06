#pragma once
#include <tuple>
#include "kitchenware.h"

namespace kitchen
{
    class stove : public kitchenware
    {
    public:
        struct color_t
        {
            using component_t = int;

            color_t(const component_t red, const component_t green, const component_t blue)
                : r(red), g(green), b(blue)
            {
            }

            component_t r{};
            component_t g{};
            component_t b{};
        };

        stove() = default;

        void color(const color_t& c);
        [[nodiscard]] color_t color() const;

        ~stove() override = default;

    private:
        color_t color_{ 0, 0, 0 };
    };
}
