#pragma once

namespace kitchen
{
    class kitchenware
    {
    public:
        using id_t = int;

        void number(id_t n);
        [[nodiscard]] id_t number() const;

        virtual ~kitchenware() = default;

    protected:
        kitchenware() = default;

    private:
        id_t number_ = 0;
    };
}
