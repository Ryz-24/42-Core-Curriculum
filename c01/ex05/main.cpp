#include "Harl.hpp"
#include <iostream>

int main()
{
    Harl harl;

    std::cout << "--- each level once ---" << std::endl;
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");

    std::cout << std::endl << "--- Harl complains a lot ---" << std::endl;
    std::string levels[6] = {"ERROR", "DEBUG", "WARNING", "ERROR", "INFO", "ERROR"};
    for (int i = 0; i < 6; i++)
        harl.complain(levels[i]);

    std::cout << std::endl << "--- unknown levels ---" << std::endl;
    harl.complain("debug");
    harl.complain("CRITICAL");
    harl.complain("");
    return 0;
}
