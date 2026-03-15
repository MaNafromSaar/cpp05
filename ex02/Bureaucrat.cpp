
// ===== Auto-generated stubs for Bureaucrat (append-only block) =====
#include "Bureaucrat.hpp"
#include "AForm.hpp"

// ── Orthodox Canonical Form ──────────────────────────────────────────────────

Bureaucrat::Bureaucrat() : name("Constant"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name((name != "") ? name : "Anton"), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : name(other.name), grade(other.grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
    if (this != &other)
    {
        grade = other.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {}

// ── Member operators ─────────────────────────────────────────────────────────

Bureaucrat& Bureaucrat::operator++()
{
    if (grade < 2)
        throw GradeTooHighException();
    grade -= 1;
    return *this;
}

Bureaucrat Bureaucrat::operator++(int)
{
    if (grade < 2)
        throw GradeTooHighException();
    Bureaucrat temp = *this;
    grade -= 1;
    return temp;
}

Bureaucrat& Bureaucrat::operator--()
{
    if (grade > 149)
        throw GradeTooLowException();
    grade += 1;
    return *this;
}

Bureaucrat Bureaucrat::operator--(int)
{
    if (grade > 149)
        throw GradeTooLowException();
    Bureaucrat temp = *this;
    grade += 1;
    return temp;
}

bool Bureaucrat::operator==(const Bureaucrat& other) const
{
    return (grade == other.grade && name == other.name);
}

bool Bureaucrat::operator!=(const Bureaucrat& other) const
{
    return (grade != other.grade || name != other.name);
}

bool Bureaucrat::operator>(const Bureaucrat& other) const
{
    return (grade < other.grade);
}

bool Bureaucrat::operator<(const Bureaucrat& other) const
{
    return (grade > other.grade);
}

bool Bureaucrat::operator>=(const Bureaucrat& other) const
{
    return !(grade > other.grade);
}

bool Bureaucrat::operator<=(const Bureaucrat& other) const
{
    return !(grade < other.grade);
}
// ===== End auto-generated stubs for Bureaucrat =====

std::string Bureaucrat::getName() const
{
    return name;
}

unsigned int Bureaucrat::getGrade() const
{
    return grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() 
{
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() 
{
    return "Grade is too low!";
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b)
{
    out << b.getName() << ", bureaucrat grade " << b.getGrade() << "." << std::endl;
    return out;
}

void Bureaucrat::signAForm(AForm& form) const
{
    try
    {
        form.beSigned(*this);
        std::cout << name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeAForm(const AForm& form) const
{
    try
    {
        form.execute(*this);
        std::cout << name << " executed " << form.getName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
