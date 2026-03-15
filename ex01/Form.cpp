#include "Form.hpp"
#include "Bureaucrat.hpp"

// ── Orthodox Canonical Form ──────────────────────────────────────────────────

// Default: lowest possible grades so it is a valid-but-useless form
Form::Form() : name("default"), isSigned(false), signGrade(150), execGrade(150) {}

Form::Form(const std::string& name, unsigned int signGrade, unsigned int execGrade)
    : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
}

// Copy constructor uses initialiser list to re-initialise const members
Form::Form(const Form& other)
    : name(other.name), isSigned(other.isSigned),
      signGrade(other.signGrade), execGrade(other.execGrade) {}

// Assignment can only transfer the mutable field; const members cannot be reassigned
Form& Form::operator=(const Form& other)
{
    if (this != &other)
        isSigned = other.isSigned;
    return *this;
}

Form::~Form() {}

// ── Getters ──────────────────────────────────────────────────────────────────

std::string  Form::getName()      const { return name; }
bool         Form::getIsSigned()  const { return isSigned; }
unsigned int Form::getSignGrade() const { return signGrade; }
unsigned int Form::getExecGrade() const { return execGrade; }

// ── Core logic ───────────────────────────────────────────────────────────────

void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > signGrade)
        throw GradeTooLowException();
    isSigned = true;
}

// ── Exception messages ───────────────────────────────────────────────────────

const char* Form::GradeTooHighException::what() const throw()
{
    return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form grade is too low!";
}

// ── Insertion operator ───────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& out, const Form& f)
{
    out << "Form \"" << f.getName() << "\""
        << " | signed: "     << (f.getIsSigned() ? "yes" : "no")
        << " | sign grade: " << f.getSignGrade()
        << " | exec grade: " << f.getExecGrade()
        << std::endl;
    return out;
}
