#pragma once
#include "electric_stove.h"
#include "saucepan.h"

namespace kitchen
{
    class slow_cooker final : public electric_stove, public saucepan
    {
    public:
        slow_cooker() = default;

        void is_pressure_cooker(bool b);
        [[nodiscard]] bool is_pressure_cooker() const;

    private:
        bool is_pressure_cooker_ = false;
    };
}
