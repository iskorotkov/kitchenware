#include "saucepan.h"

void kitchen::saucepan::volume(const volume_t v)
{
    volume_ = v;
}

kitchen::saucepan::volume_t kitchen::saucepan::volume() const
{
    return volume_;
}
