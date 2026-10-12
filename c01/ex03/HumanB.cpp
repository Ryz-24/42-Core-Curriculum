#include "HumanB.hpp"

HumanB::HumanB(std::string name) :
        name(name), weapon(NULL)
{}

void HumanB::setWeapon(Weapon &weapon)
{
    this->weapon = &weapon;
}

void HumanB::attack() const
{
    if (weapon == NULL)
    {
        std::cout << name << " has no weapon to attack with!" << std::endl;
        return;
    }

    std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}