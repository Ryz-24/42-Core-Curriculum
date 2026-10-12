#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    // Test from the subject: HumanA is armed from construction
    {
        Weapon club = Weapon("crude spiked club");

        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    // Test from the subject: HumanB gets a weapon later
    {
        Weapon club = Weapon("crude spiked club");

        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
    // Extra: HumanB with no weapon must not crash
    {
        HumanB tom("Tom");
        tom.attack();
    }
    return 0;
}
