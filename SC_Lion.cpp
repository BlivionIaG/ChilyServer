#include "SC_Lion.hpp"

void SC_Lion::attack(SC_Animal &target)
{
    if (target.getHP() > 0)
    {
        addHP((int)target.getHP() / 4);
        target.setHP(0);
        kills++;
    }
}