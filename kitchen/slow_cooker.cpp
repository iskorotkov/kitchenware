#include "slow_cooker.h"

void kitchen::slow_cooker::is_pressure_cooker(const bool b)
{
    is_pressure_cooker_ = b;
}

bool kitchen::slow_cooker::is_pressure_cooker() const
{
    return is_pressure_cooker_;
}

void kitchen::slow_cooker::print(std::ostream& out, bool full_output) const
{
    if (full_output)
    {
        out << "slow cooker\n";
        kitchenware::print(out, false);
        stove::print(out, false);
        electric_stove::print(out, false);
        saucepan::print(out, false);
    }
    out << (is_pressure_cooker() ? "is pressure cooker" : "is not pressure cooker") << "\n";
}
