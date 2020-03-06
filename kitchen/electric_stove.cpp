#include "electric_stove.h"

void kitchen::electric_stove::power(const power_t p)
{
    power_ = p;
}

kitchen::electric_stove::power_t kitchen::electric_stove::power() const
{
    return power_;
}
