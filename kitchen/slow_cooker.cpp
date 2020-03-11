#include "slow_cooker.h"

void kitchen::slow_cooker::is_pressure_cooker(const bool b)
{
    is_pressure_cooker_ = b;
}

bool kitchen::slow_cooker::is_pressure_cooker() const
{
    return is_pressure_cooker_;
}

void kitchen::slow_cooker::print(std::ostream& out) const
{
    electric_stove::print(out);
    saucepan::print(out);
    out << "is pressure cooker = " << is_pressure_cooker() << "\n";
}
