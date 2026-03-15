#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    Bureaucrat intern("Intern", 150);
    Bureaucrat officer("Officer", 40);
    Bureaucrat boss("Boss", 1);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm robo("Bender");
    PresidentialPardonForm pardon("Arthur Dent");

    std::cout << "=== Unsigned execution should fail ===" << std::endl;
    intern.executeForm(shrub);

    std::cout << "\n=== Signing tests ===" << std::endl;
    intern.signForm(shrub);
    officer.signForm(shrub);

    intern.signForm(robo);
    officer.signForm(robo);

    officer.signForm(pardon);
    boss.signForm(pardon);

    std::cout << "\n=== Execution tests ===" << std::endl;
    intern.executeForm(shrub);
    officer.executeForm(shrub);

    officer.executeForm(robo);
    boss.executeForm(robo);
    boss.executeForm(robo);
    boss.executeForm(robo);

    officer.executeForm(pardon);
    boss.executeForm(pardon);

    return 0;
}