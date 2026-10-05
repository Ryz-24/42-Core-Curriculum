#include "PhoneBook.hpp"

int main(void)
{
    PhoneBook    phonebook;
    std::string  command;

    while (true)
    {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
            break;
        if (command == "ADD" || command == "add")
            phonebook.add_contacts();
        else if (command == "SEARCH" || command == "search")
            phonebook.search_contacts();
        else if (command == "EXIT" || command == "exit")
            break;
    }
    return (0);
}

/*
    Might wanna add to the set functions:
    Verify the information entered
        - Like the case when entering a number in FirstName
        - or a string in Number
    Aceepting lower case when entering a command
        - like "add" insted of "ADD"
    
    Might wanna remove from the contact.cpp:
    The constructers 
*/
