#include "kitchenware.h"

void kitchen::kitchenware::number(const id_t n)
{
    number_ = n;
}

kitchen::kitchenware::id_t kitchen::kitchenware::number() const
{
    return number_;
}
