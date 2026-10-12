#include "Zombie.hpp"

int main()
{
    Zombie *z = newZombie("heap");
    z->announce();

    randomChump("stack");

    delete z;
    return (0);
}