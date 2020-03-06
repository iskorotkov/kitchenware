#include "gas_stove.h"

void kitchen::gas_stove::gas_waste(const gas_waste_t waste)
{
    gas_waste_ = waste;
}

kitchen::gas_stove::gas_waste_t kitchen::gas_stove::gas_waste() const
{
    return gas_waste_;
}
