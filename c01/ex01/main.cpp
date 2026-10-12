#include "Zombie.hpp"

int main()
{
    int n = 3;

    Zombie *horde = zombieHorde(n, "Zombie");
    for (int i = 0; i < n; i++)
        horde[i].announce();

    delete[] horde;
    return 0;
}