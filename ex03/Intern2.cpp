#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cctype>

// Alternative implementation: switch-style dispatch based on first 3 chars.
// This file is not part of the default Makefile build.

static int prefixKey(const std::string& formName)
{
    if (formName.length() < 3)
        return -1;

    const int c0 = std::tolower(static_cast<unsigned char>(formName[0]));
    const int c1 = std::tolower(static_cast<unsigned char>(formName[1]));
    const int c2 = std::tolower(static_cast<unsigned char>(formName[2]));

    return (c0 << 16) | (c1 << 8) | c2;
}

Intern::Intern() {}

Intern::Intern(const Intern& other)
{
    (void)other;
}

Intern& Intern::operator=(const Intern& other)
{
    (void)other;
    return *this;
}

Intern::~Intern() {}

AForm* Intern::createShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target)
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidential(const std::string& target)
{
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    // Keys: 'shr', 'rob', 'pre'
    switch (prefixKey(formName))
    {
        case ('s' << 16) | ('h' << 8) | 'r':
            std::cout << "Intern creates " << formName << std::endl;
            return createShrubbery(target);
        case ('r' << 16) | ('o' << 8) | 'b':
            std::cout << "Intern creates " << formName << std::endl;
            return createRobotomy(target);
        case ('p' << 16) | ('r' << 8) | 'e':
            std::cout << "Intern creates " << formName << std::endl;
            return createPresidential(target);
        default:
            std::cout << "Intern couldn't create form \"" << formName
                      << "\": unknown form name" << std::endl;
            return NULL;
    }
}
