#include "Contact.hpp"

void Contact::setFirstName(std::string FirstName)
{
    this->FirstName = FirstName;
}
void Contact::setLastName(std::string LastName)
{
    this->LastName = LastName;
}
void Contact::setNickname(std::string Nickname)
{
    this->Nickname = Nickname;
}
void Contact::setPhoneNumber(std::string PhoneNumber)
{
    this->PhoneNumber = PhoneNumber;
}
void Contact::setDarkestSecret(std::string DarkestSecret)
{
    this->DarkestSecret = DarkestSecret;
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
