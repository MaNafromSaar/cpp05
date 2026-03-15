#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    Bureaucrat reese("Reese", 150);
    Bureaucrat malcolm("Malcolm", 40);
    Bureaucrat francis("Francis", 1);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm robo("Bender");
    PresidentialPardonForm pardon("Arthur Dent");

    std::cout << "=== Unsigned execution should fail ===" << std::endl;
    reese.executeAForm(shrub);

    std::cout << "\n=== Signing tests ===" << std::endl;
    reese.signAForm(shrub);
    malcolm.signAForm(shrub);

    reese.signAForm(robo);
    malcolm.signAForm(robo);

    malcolm.signAForm(pardon);
    francis.signAForm(pardon);

    std::cout << "\n=== Execution tests ===" << std::endl;
    reese.executeAForm(shrub);
    malcolm.executeAForm(shrub);

    malcolm.executeAForm(robo);
    francis.executeAForm(robo);
    francis.executeAForm(robo);
    francis.executeAForm(robo);

    malcolm.executeAForm(pardon);
    francis.executeAForm(pardon);

    return 0;
}