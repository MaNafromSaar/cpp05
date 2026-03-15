#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP


// ===== Auto-generated Orthodox Canonical Form (adjust placeholders as needed) =====
#include <string>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
    const std::string target;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(const std::string& target);
    RobotomyRequestForm(const RobotomyRequestForm& other);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
    virtual ~RobotomyRequestForm();
    virtual void executeAction() const;
};
// ===== End auto-generated block =====
#endif
