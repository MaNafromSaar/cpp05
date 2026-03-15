#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>

class Bureaucrat;  // forward declaration — avoids circular include

class Form
{
private:
    const std::string   name;
    bool                isSigned;
    const unsigned int  signGrade;
    const unsigned int  execGrade;

public:
    // Orthodox Canonical Form
    Form();
    Form(const std::string& name, unsigned int signGrade, unsigned int execGrade);
    Form(const Form& other);
    Form& operator=(const Form& other);  // only copies isSigned; const members can't be reassigned
    ~Form();

    // Getters
    std::string  getName()      const;
    bool         getIsSigned()  const;
    unsigned int getSignGrade() const;
    unsigned int getExecGrade() const;

    // Core logic
    void beSigned(const Bureaucrat& b);

    // Exception classes (OCF not required per subject)
    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const Form& f);

#endif
