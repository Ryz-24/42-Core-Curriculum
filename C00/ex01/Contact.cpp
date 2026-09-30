#include "Contact.hpp"

Contact::Contact() :    FirstName(""),
                        LastName(""),
                        Nickname(""),
                        PhoneNumber(""),
                        DarkestSecret("")
{}
Contact::Contact(std::string FirstName, std::string LastName, std::string Nickname, std::string PhoneNumber, std::string DarkestSecret)
                :   FirstName(FirstName),
                    LastName(LastName),
                    Nickname(Nickname),
                    PhoneNumber(PhoneNumber),
                    DarkestSecret(DarkestSecret)
{}

bool Contact::setFirstName(std::string FirstName)
{
    if(FirstName.empty())
        return (false);
    this->FirstName = FirstName;
    return (true);
}
bool Contact::setLastName(std::string LastName)
{
    if (LastName.empty())
        return (false);
    this->LastName = LastName;
    return (true);
}
bool Contact::setNickname(std::string Nickname)
{
    if (Nickname.empty())
        return (false);
    this->Nickname = Nickname;
    return (true);
}
bool Contact::setPhoneNumber(std::string PhoneNumber)
{
    if (PhoneNumber.empty())
        return (false);
    this->PhoneNumber = PhoneNumber;
    return (true);
}
bool Contact::setDarkestSecret(std::string DarkestSecret)
{
    if (DarkestSecret.empty())
        return (false);
    this->DarkestSecret = DarkestSecret;
    return (true);
}


std::string Contact::getFirstName() const
{
    return (this->FirstName);
}
std::string Contact::getLastName() const
{
    return (this->LastName);
}
std::string Contact::getNickname() const
{
    return (this->Nickname);
}
std::string Contact::getPhoneNumber() const
{
    return (this->PhoneNumber);
}
std::string Contact::getDarkestSecret() const
{
    return (this->DarkestSecret);
}
