#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <iostream>

static void testFormCreationAndExecution(
    Intern& intern,
    Bureaucrat& signer,
    Bureaucrat& executor,
    const std::string& formName,
    const std::string& target)
{
    std::cout << "\n=== Test: " << formName << " (target: " << target << ") ===" << std::endl;

    AForm* form = intern.makeForm(formName, target);
    if (form == NULL)
        return;

    std::cout << *form;
    signer.signForm(*form);
    executor.executeForm(*form);

    delete form;
}

int main()
{
    Intern intern;
    Bureaucrat malcolm("Malcolm", 40);
    Bureaucrat francis("Francis", 1);

    testFormCreationAndExecution(intern, malcolm, francis, "shrubbery creation", "home");
    testFormCreationAndExecution(intern, malcolm, francis, "robotomy request", "Bender");
    testFormCreationAndExecution(intern, francis, francis, "presidential pardon", "Arthur Dent");

    std::cout << "\n=== Test: invalid form name ===" << std::endl;
    AForm* invalid = intern.makeForm("coffee request", "Office");
    if (invalid != NULL)
        delete invalid;

    return 0;
}
