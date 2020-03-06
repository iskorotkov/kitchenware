#include "slow_cooker.h"

void kitchen::slow_cooker::is_pressure_cooker(const bool b)
{
    is_pressure_cooker_ = b;
}

bool kitchen::slow_cooker::is_pressure_cooker() const
{
    return is_pressure_cooker_;
}
