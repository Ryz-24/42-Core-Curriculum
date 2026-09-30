#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook
{
    private:
        int count;
        int lastAdded;
        Contact contacts[8];
    public:
        PhoneBook();
        bool add_contacts();
        void display_contacts();
        void search_contacts();
};

#endif