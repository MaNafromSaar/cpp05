
// ===== Auto-generated stubs for ShrubberyCreationForm (append-only block) =====
#include "ShrubberyCreationForm.hpp"

// ── Orthodox Canonical Form ──────────────────────────────────────────────────

ShrubberyCreationForm::ShrubberyCreationForm() : AForm"ShrubberyCreationForm", 145, 137), target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : AForm()"ShrubberyCreationForm", 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other), target(other.target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other)
    {
        AForm::operator=(other);
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}
// ===== End auto-generated stubs for ShrubberyCreationForm =====

void ShrubberyCreationForm::executeAction() const
{
    std::ofstream out((target + "_shrubbery").c_str());
    if (!out.is_open())
        throw std::runtime_error("could not open shrubbery output file");

    out <<
"       _-_\n"
"    /~~   ~~\\\n"
" /~~         ~~\\\n"
"{        . .     }\n"
" \\  _-   v -_  /\n"
"   ~  \\\\ //  ~\n"
"_- -   | | _- _\n"
"  _ -  | |   -_\n"
"      // \\\\\n";

    out.close();
}