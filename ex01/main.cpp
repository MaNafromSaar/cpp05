#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <sstream>

static const char* C_RESET  = "\033[0m";
static const char* C_GREEN  = "\033[38;5;46m";
static const char* C_RED    = "\033[38;5;196m";
static const char* C_BROWN  = "\033[38;5;94m";
static const char* C_ORANGE = "\033[38;5;214m";
static const char* C_YELLOW = "\033[38;5;226m";

static const char* bureaucratColor(const std::string& name)
{
    if (name == "Reese")
        return C_BROWN;
    if (name == "Malcolm")
        return C_ORANGE;
    if (name == "Francis")
        return C_YELLOW;
    return C_RESET;
}

static std::string colorize(const std::string& text, const char* color)
{
    return std::string(color) + text + C_RESET;
}

static std::string toStringUnsigned(unsigned int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

static std::string formatBureaucrat(const Bureaucrat& b)
{
    return colorize(b.getName(), bureaucratColor(b.getName()))
        + ", bureaucrat grade " + toStringUnsigned(b.getGrade()) + ".";
}

static std::string formatForm(const Form& f)
{
    const std::string signedText = f.getIsSigned()
        ? colorize("yes", C_GREEN)
        : colorize("no", C_RED);

    return "Form \"" + f.getName() + "\""
        + " | signed: " + signedText
        + " | sign grade: " + toStringUnsigned(f.getSignGrade())
        + " | exec grade: " + toStringUnsigned(f.getExecGrade());
}

int main()
{
    const Bureaucrat lowPrototype("Reese", 52);
    const Bureaucrat midPrototype("Malcolm", 50);
    const Bureaucrat highPrototype("Francis", 1);

    const Form easyPrototype("PrankPermit", 50, 25);
    const Form strictPrototype("RemoteControlAccess", 49, 20);
    const Form copyPrototype("BlankThought", 50, 50);

    std::cout << "=== Form construction: valid values ===" << std::endl;
    try {
        std::cout << "Input: name=" << easyPrototype.getName()
                  << ", signGrade=" << easyPrototype.getSignGrade()
                  << ", execGrade=" << easyPrototype.getExecGrade() << std::endl;
        std::cout << formatForm(easyPrototype) << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== Form construction: invalid grades ===" << std::endl;
    std::cout << "Input: name=HighSign, signGrade=0, execGrade=10" << std::endl;
    try { Form highSign("HighSign", 0, 10); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    std::cout << "Input: name=LowExec, signGrade=10, execGrade=151" << std::endl;
    try { Form lowExec("LowExec", 10, 151); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    std::cout << std::endl << "=== beSigned: direct success and failure ===" << std::endl;
    try {
        Form copySource(copyPrototype);
        Form strict(strictPrototype);
        Bureaucrat high(highPrototype);
        Bureaucrat mid(midPrototype);

        std::cout << "Input form:        " << std::endl << formatForm(copySource) << std::endl;
        std::cout << "Input bureaucrat:  " << formatBureaucrat(high) << std::endl;
        copySource.beSigned(high);
        std::cout << "After beSigned:    " << std::endl << formatForm(copySource) << std::endl;

        std::cout << "Input form:        " << std::endl << formatForm(strict) << std::endl;
        std::cout << "Input bureaucrat:  " << formatBureaucrat(mid) << std::endl;
        strict.beSigned(mid);
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== signForm: threshold by promotion ===" << std::endl;
    try {
        Bureaucrat low(lowPrototype);
        Form easy(easyPrototype);

        std::cout << "Initial bureaucrat: " << formatBureaucrat(low) << std::endl;
        std::cout << "Initial form:       " << std::endl << formatForm(easy) << std::endl;
        std::cout << "Action: Reese tries to sign at grade 52" << std::endl;
        low.signForm(easy);
        std::cout << "Form after try:     " << std::endl << formatForm(easy) << std::endl;

        std::cout << "Action: promote Reese twice" << std::endl;
        ++low;
        ++low;
        std::cout << "Promoted bureaucrat: " << formatBureaucrat(low) << std::endl;

        std::cout << "Action: Reese tries again at grade 50" << std::endl;
        low.signForm(easy);
        std::cout << "Form after retry:    " << std::endl << formatForm(easy) << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== signForm: threshold by demotion ===" << std::endl;
    try {
        Bureaucrat mid(midPrototype);
        Form copySource(copyPrototype);
        Form strict(strictPrototype);

        std::cout << "Initial bureaucrat: " << formatBureaucrat(mid) << std::endl;
        std::cout << "Initial form:       " << std::endl << formatForm(copySource) << std::endl;
        std::cout << "Action: Malcolm signs exactly at required grade" << std::endl;
        mid.signForm(copySource);
        std::cout << "Form after sign:    " << std::endl << formatForm(copySource) << std::endl;

        std::cout << "Action: demote Malcolm once" << std::endl;
        --mid;
        std::cout << "Demoted bureaucrat: " << formatBureaucrat(mid) << std::endl;
        std::cout << "Next form:          " << std::endl << formatForm(strict) << std::endl;
        std::cout << "Action: Malcolm tries to sign a stricter form" << std::endl;
        mid.signForm(strict);
        std::cout << "Form after try:     " << std::endl << formatForm(strict) << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== Form OCF semantics ===" << std::endl;
    try {
        Bureaucrat high(highPrototype);
        Form copySource(copyPrototype);
        Form assignedTarget(strictPrototype);

        std::cout << "Input bureaucrat:" << std::endl;
        std::cout << formatBureaucrat(high) << std::endl;
        std::cout << "Input source form before signing:" << std::endl;
        std::cout << formatForm(copySource) << std::endl;
        high.signForm(copySource);
        std::cout << "Source form after signing:" << std::endl;
        std::cout << formatForm(copySource) << std::endl;

        Form copy(copySource);
        std::cout << "Copy constructor input: source form above" << std::endl;
        std::cout << "Copy-constructed form:" << std::endl;
        std::cout << formatForm(copy) << std::endl;

        std::cout << "Assignment input target before:" << std::endl;
        std::cout << formatForm(assignedTarget) << std::endl;
        std::cout << "Assignment input source:" << std::endl;
        std::cout << formatForm(copySource) << std::endl;
        assignedTarget = copySource;
        std::cout << "Assignment target after:" << std::endl;
        std::cout << formatForm(assignedTarget) << std::endl;
        std::cout << "Note: name/grades stay, signed state is copied" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    return 0;
}
/*
Compile with:
c++ -Wall -Wextra -Werror -std=c++98 Bureaucrat.cpp Form.cpp main.cpp -o form
*/