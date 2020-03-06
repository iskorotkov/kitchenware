#pragma once
#include "kitchenware.h"

namespace kitchen
{
    class saucepan : public kitchenware
    {
    public:
        using volume_t = double;

        saucepan() = default;

        void volume(volume_t v);
        [[nodiscard]] volume_t volume() const;

        ~saucepan() override = default;

    private:
        volume_t volume_ = 0.0;
    };
}
