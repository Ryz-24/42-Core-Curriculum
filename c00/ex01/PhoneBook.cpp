#include "PhoneBook.hpp"

static bool validName(const std::string &str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!std::isalpha(str[i]) && str[i] != ' ')
            return (false);
    }
    return (true);
}

static bool validPhoneNumber(const std::string &str)
{
    bool hasDigit = false;

    for (size_t i = 0; i < str.length(); i++)
    {
        if (std::isdigit(str[i]))
            hasDigit = true;
        else if (str[i] == '+' && i == 0)
            continue;
        else
            return (false);
    }
    return (hasDigit);
}

static bool parseIndex(const std::string &line, int &out)
{
    if (line.empty())
        return (false);

    int n = 0;
    for (size_t i = 0; i < line.length(); i++)
    {
        if (line[i] < '0' || line[i] > '9')
            return (false);
        n = n * 10 + (line[i] - '0');
    }
    out = n;
    return (true);
}

static std::string truncate(std::string s)
{
    if (s.length() > 10)
        return (s.substr(0, 9) + ".");
    return (s);
}

static bool promptField(const std::string &label, std::string &out)
{
    while (true)
    {
        std::cout << label << ": ";
        if (!std::getline(std::cin, out))
            return (false);
        if (!out.empty())
            return (true);
        std::cout << "This field cannot be empty." << std::endl;
    }
}

static bool promptName(const std::string &label, std::string &out)
{
    while (true)
    {
        if (!promptField(label, out))
            return (false);
        if (validName(out))
            return (true);
        std::cout << "This field can only contain letters and spaces." << std::endl;
    }
}

static bool promptPhone(const std::string &label, std::string &out)
{
    while (true)
    {
        if (!promptField(label, out))
            return (false);
        if (validPhoneNumber(out))
            return (true);
        std::cout << "Invalid phone number." << std::endl;
    }
}

PhoneBook::PhoneBook() : count(0),
                         lastAdded(-1)
{
}

bool PhoneBook::add_contacts()
{
    std::string first;
    std::string last;
    std::string nick;
    std::string phone;
    std::string secret;

    if (!promptName("First name", first))
        return (false);
    if (!promptName("Last name", last))
        return (false);
    if (!promptField("Nickname", nick))
        return (false);
    if (!promptPhone("Phone number", phone))
        return (false);
    if (!promptField("Darkest secret", secret))
        return (false);

    lastAdded = (lastAdded + 1) % 8;
    contacts[lastAdded].setFirstName(first);
    contacts[lastAdded].setLastName(last);
    contacts[lastAdded].setNickname(nick);
    contacts[lastAdded].setPhoneNumber(phone);
    contacts[lastAdded].setDarkestSecret(secret);
    if (count < 8)
        count++;
    return (true);
}

void PhoneBook::display_contacts()
{
    if (count == 0)
    {
        std::cout << "The phonebook is empty." << std::endl;
        return;
    }
    std::cout << "|" << std::setw(10) << "Index"
              << "|" << std::setw(10) << "First Name"
              << "|" << std::setw(10) << "Last Name"
              << "|" << std::setw(10) << "Nickname"
              << "|" << std::endl;
    for (int i = 0; i < count; i++)
    {
        std::cout << "|" << std::setw(10) << (i + 1)
                  << "|" << std::setw(10) << truncate(contacts[i].getFirstName())
                  << "|" << std::setw(10) << truncate(contacts[i].getLastName())
                  << "|" << std::setw(10) << truncate(contacts[i].getNickname())
                  << "|" << std::endl;
    }
}

void PhoneBook::search_contacts()
{
    if (count == 0)
    {
        std::cout << "The phonebook is empty." << std::endl;
        return;
    }
    display_contacts();

    std::string line;
    std::cout << "Enter the index to display: ";
    if (!std::getline(std::cin, line))
        return;

    int index;
    if (!parseIndex(line, index) || index < 1 || index > count)
    {
        std::cout << "Invalid index." << std::endl;
        return;
    }

    Contact c = contacts[index - 1];
    std::cout << "First name    : " << c.getFirstName() << std::endl;
    std::cout << "Last name     : " << c.getLastName() << std::endl;
    std::cout << "Nickname      : " << c.getNickname() << std::endl;
    std::cout << "Phone number  : " << c.getPhoneNumber() << std::endl;
    std::cout << "Darkest secret: " << c.getDarkestSecret() << std::endl;
}