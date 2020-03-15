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
        electric_stove::print(out);
        saucepan::print(out, false);
    }
    out << "is pressure cooker = " << is_pressure_cooker() << "\n";
}
