#include "AForm.hpp"
#include "Bureaucrat.hpp"

// ── Orthodox Canonical Form ──────────────────────────────────────────────────

// Default: lowest possible grades so it is a valid-but-useless Form
AForm::AForm() : name("default"), isSigned(false), signGrade(150), execGrade(150) {}

AForm::AForm(const std::string& name, unsigned int signGrade, unsigned int execGrade)
    : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
}

// Copy constructor uses initialiser list to re-initialise const members
AForm::AForm(const AForm& other)
    : name(other.name), isSigned(other.isSigned),
      signGrade(other.signGrade), execGrade(other.execGrade) {}

// Assignment can only transfer the mutable field; const members cannot be reassigned
AForm& AForm::operator=(const AForm& other)
{
    if (this != &other)
        isSigned = other.isSigned;
    return *this;
}

AForm::~AForm() {}

// ── Getters ──────────────────────────────────────────────────────────────────

std::string  AForm::getName()      const { return name; }
bool         AForm::getIsSigned()  const { return isSigned; }
unsigned int AForm::getSignGrade() const { return signGrade; }
unsigned int AForm::getExecGrade() const { return execGrade; }

// ── Core logic ───────────────────────────────────────────────────────────────

void AForm::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > signGrade)
        throw GradeTooLowException();
    isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const
{
    if (!isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > execGrade)
        throw GradeTooLowException();
    executeAction();
}

// ── Exception messages ───────────────────────────────────────────────────────

const char* AForm::GradeTooHighException::what() const throw()
{
    return "Form grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Form grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return "Form is not signed!";
}

// ── Insertion operator ───────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& out, const AForm& f)
{
    out << "Form \"" << f.getName() << "\""
        << " | signed: "     << (f.getIsSigned() ? "yes" : "no")
        << " | sign grade: " << f.getSignGrade()
        << " | exec grade: " << f.getExecGrade()
        << std::endl;
    return out;
}
