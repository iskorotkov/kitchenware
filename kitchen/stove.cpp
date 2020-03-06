#include "stove.h"

void kitchen::stove::color(const color_t& c)
{
    color_ = c;
}

kitchen::stove::color_t kitchen::stove::color() const
{
    return color_;
}
