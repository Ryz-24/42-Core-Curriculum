#ifndef CONTACT_HPP
#define CONTACT_HPP

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
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickname() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;

        void setFirstName(std::string FirstName);
        void setLastName(std::string LastName);
        void setNickname(std::string Nickname);
        void setPhoneNumber(std::string PhoneNumber);
        void setDarkestSecret(std::string DarkestSecret);
};
#endif
