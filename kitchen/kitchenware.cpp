#include "kitchenware.h"

void kitchen::kitchenware::number(const id_t n)
{
    number_ = n;
}

kitchen::kitchenware::id_t kitchen::kitchenware::number() const
{
    return number_;
}

void kitchen::kitchenware::print(std::ostream& out, bool full_output) const
{
    if (full_output)
    {
        out << "kitchenware\n";
    }
    out << "id = " << number() << "\n";
}
