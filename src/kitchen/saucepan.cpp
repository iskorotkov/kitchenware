#include "saucepan.h"

void kitchen::saucepan::volume(const volume_t v)
{
    volume_ = v;
}

kitchen::saucepan::volume_t kitchen::saucepan::volume() const
{
    return volume_;
}

void kitchen::saucepan::print(std::ostream& out, bool full_output) const
{
    if (full_output)
    {
        out << "saucepan\n";
        kitchenware::print(out, false);
    }
    out << "volume = " << volume() << "\n";
}
