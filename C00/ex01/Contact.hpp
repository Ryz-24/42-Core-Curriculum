#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>

class Contact
{
    private:
        std::string FirstName;
        std::string LastName;
        std::string Nickname;
        std::string PhoneNumber;
        std::string DarkestSecret;
        
    public:
        Contact();
        Contact(std::string FirstName, std::string LastName, std::string Nickname, std::string PhoneNumber, std::string DarkestSecret);
        
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickname() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;

        bool setFirstName(std::string FirstName);
        bool setLastName(std::string LastName);
        bool setNickname(std::string Nickname);
        bool setPhoneNumber(std::string PhoneNumber);
        bool setDarkestSecret(std::string DarkestSecret);
};
#endif
