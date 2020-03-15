#pragma once
#include <tuple>
#include "kitchenware.h"

namespace kitchen
{
    class stove : public virtual kitchenware
    {
    public:
        class color_t
        {
        public:
            using component_t = int;

            color_t(const component_t red, const component_t green, const component_t blue);

            [[nodiscard]] std::string to_string() const;

        private:
            component_t r{};
            component_t g{};
            component_t b{};
        };

        stove() = default;

        void color(const color_t& c);
        [[nodiscard]] color_t color() const;

        void print(std::ostream& out) const override;

        ~stove() override = default;

    private:
        color_t color_{ 0, 0, 0 };
    };
}
