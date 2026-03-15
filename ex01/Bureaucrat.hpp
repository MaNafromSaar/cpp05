#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP


// ===== Auto-generated Orthodox Canonical Form (adjust placeholders as needed) =====
#include <string>
#include <iostream>
#include <sstream>

class Bureaucrat
{
private:
    std::string     name;
    unsigned int    grade;

public:
    Bureaucrat();
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

    // NOTE: Placeholder signatures — update types/semantics to match real behavior.
    Bureaucrat& operator++();
    Bureaucrat  operator++(int); 
    Bureaucrat& operator--();          // TODO: choose meaningful return type
    Bureaucrat  operator--(int);       // TODO: choose meaningful return type
    bool operator==(const Bureaucrat& other) const;
    bool operator>(const Bureaucrat& other) const;
    bool operator<(const Bureaucrat& other) const;
    bool operator>=(const Bureaucrat& other) const;
    bool operator<=(const Bureaucrat& other) const;

    std::string getName() const;
    unsigned int getGrade() const;

    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& b);

#endif
