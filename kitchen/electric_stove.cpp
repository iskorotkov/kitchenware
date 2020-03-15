#include "electric_stove.h"

void kitchen::electric_stove::power(const power_t p)
{
    power_ = p;
}

kitchen::electric_stove::power_t kitchen::electric_stove::power() const
{
    return power_;
}

void kitchen::electric_stove::print(std::ostream& out, bool full_output) const
{
    if (full_output)
    {
        stove::print(out);
    }
    out << "power = " << power() << "\n";
}
