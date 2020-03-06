#pragma once
#include "stove.h"

namespace kitchen
{
    class electric_stove : public stove
    {
    public:
        using power_t = double;

        electric_stove() = default;

        void power(power_t p);
        [[nodiscard]] power_t power() const;

        ~electric_stove() override = default;

    private:
        power_t power_ = 0;
    };
}
