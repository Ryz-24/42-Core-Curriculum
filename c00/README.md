*This project has been created as part of the 42 curriculum by rzaatreh.*

# CPP MODULE 00

## Description

**CPP Module 00** is the first module of the C++ curriculum at 42. Its purpose is to introduce the fundamental concepts of **C++ programming** and the differences between C and C++.

The module focuses on learning the basics of:

* Classes and objects
* Encapsulation
* Member functions
* Constructors
* Access specifiers
* Namespaces
* Standard input and output
* Strings
* Basic C++ syntax and conventions



## Exercises

CPP Module 00 contains the following exercises:

| Exercise | Topic | Description |
| -------- | ----- | ----------- |
| `ex00` | Megaphone | Introduces basic C++ syntax and string manipulation |
| `ex01` | PhoneBook | Introduces classes, objects, private/public members, and user interaction |

---

## ex00 — Megaphone

The first exercise introduces basic C++ syntax.

The program takes command-line arguments and prints them in uppercase.

Example:

```bash
./megaphone "hello world"
````

 Output:

```
HELLO WORLD
```

 If no arguments are provided, the program prints:

```
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```


 ## ex01 — PhoneBook

 The program implements a simple phonebook containing contacts.
 
 The phonebook supports three commands:

```
ADD
SEARCH
EXIT
```

 ### ADD

 Adds a new contact to the phonebook.

 Each contact contains:

 - First name
- Last name
- Nickname
- Phone number
- Darkest secret

 The phonebook can store a maximum of **8 contacts**.

 When the phonebook is full, adding a new contact replaces the oldest contact.

 ### SEARCH

 Displays the list of stored contacts in a formatted table.

 Example:

```
     Index|First Name| Last Name|  Nickname
         0|      John|       Doe|      johny
         1|      Jane|     Smith|      jane
```

 After selecting a contact by index, the complete contact information is displayed.

 ### EXIT

 Terminates the program.

---

 ## Instructions

 ### ex00

 Navigate to the exercise directory:

```
cd ex00
```

 Compile:

```
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o megaphone
```

 Run:

```
./megaphone "Hello World"
```

---

 ### ex01

 Navigate to:

```
cd ex01
```

 Compile:

```
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o phonebook
```

 Run:

```
./phonebook
```

 Available commands:

```
ADD
SEARCH
EXIT
```

 Example:

```
ADD
SEARCH
EXIT
```


 ## Resources

- [Learn Cpp](learncpp.com)
- [C++ Language (C++98)](https://cplusplus.com/doc/oldtutorial/)
- [C++ 98 Standard](https://www.geeksforgeeks.org/cpp/cpp-98-standard/)

---

 ## AI Usage

 AI tools were used strictly as a learning assistant.

 They were used to:

- Clarify C++ syntax and concepts
- Understand the differences between C and C++
- Review encapsulation and access specifiers
- Review potential edge cases
- Improve documentation clarity
