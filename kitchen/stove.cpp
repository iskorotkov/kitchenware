#include "stove.h"
#include <string>

void kitchen::stove::color(const color_t& c)
{
    color_ = c;
}

kitchen::stove::color_t kitchen::stove::color() const
{
    return color_;
}

void kitchen::stove::print(std::ostream& out) const
{
    kitchenware::print(out);
    out << "color = " << color().to_string() << "\n";
}

kitchen::stove::color_t::color_t(const component_t red, const component_t green, const component_t blue)
    : r(red), g(green), b(blue)
{
}

std::string kitchen::stove::color_t::to_string() const
{
    return std::to_string(r) + ";"
         + std::to_string(g) + ";"
         + std::to_string(b);
}
