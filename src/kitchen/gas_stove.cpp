#include "gas_stove.h"

void kitchen::gas_stove::gas_waste(const gas_waste_t waste)
{
    gas_waste_ = waste;
}

kitchen::gas_stove::gas_waste_t kitchen::gas_stove::gas_waste() const
{
    return gas_waste_;
}

void kitchen::gas_stove::print(std::ostream& out, bool full_output) const
{
    if (full_output)
    {
        out << "gas stove\n";
        kitchenware::print(out, false);
        stove::print(out, false);
    }
    out << "gas waste = " << gas_waste() << "\n";
}
