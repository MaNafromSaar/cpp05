#ifndef AForm_HPP
#define AForm_HPP

#include <string>
#include <iostream>

class Bureaucrat;  // forward declaration — avoids circular include

class AForm
{
private:
    const std::string   name;
    bool                isSigned;
    const unsigned int  signGrade;
    const unsigned int  execGrade;

public:
    // Orthodox Canonical Form
    AForm();
    AForm(const std::string& name, unsigned int signGrade, unsigned int execGrade);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);  // only copies isSigned; const members can't be reassigned
    virtual ~AForm();

    // Getters
    std::string  getName()      const;
    bool         getIsSigned()  const;
    unsigned int getSignGrade() const;
    unsigned int getExecGrade() const;

    // Core logic
    void beSigned(const Bureaucrat& b);
    void execute(const Bureaucrat& executor) const;
    virtual void executeAction() const = 0;

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
    class FormNotSignedException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const AForm& f);

#endif
