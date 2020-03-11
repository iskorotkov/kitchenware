#pragma once
#include "stove.h"

namespace kitchen
{
    class gas_stove final : public stove
    {
    public:
        using gas_waste_t = double;

        gas_stove() = default;

        void gas_waste(gas_waste_t waste);
        [[nodiscard]] gas_waste_t gas_waste() const;

        void print(std::ostream& out) const;

    private:
        gas_waste_t gas_waste_ = 0.0;
    };
}
