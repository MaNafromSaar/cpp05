#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    // ── Bureaucrat tests (carried over from ex00) ────────────────────────────
    std::cout << "=== Bureaucrat: valid construction ===" << std::endl;
    try {
        Bureaucrat alice("Alice", 1);
        Bureaucrat bob("Bob", 150);
        std::cout << alice;
        std::cout << bob;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << "=== Bureaucrat: grade out of range ===" << std::endl;
    try { Bureaucrat bad("Bad", 0); }
    catch (std::exception& e) { std::cout << "grade 0:   " << e.what() << std::endl; }
    try { Bureaucrat bad("Bad", 151); }
    catch (std::exception& e) { std::cout << "grade 151: " << e.what() << std::endl; }

    // ── Form: valid construction ─────────────────────────────────────────────
    std::cout << std::endl << "=== Form: valid construction ===" << std::endl;
    try {
        Form f1("Tax Return", 50, 25);
        Form f2("Budget Approval", 1, 1);
        std::cout << f1;
        std::cout << f2;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    // ── Form: invalid grades ─────────────────────────────────────────────────
    std::cout << "=== Form: grade too high (sign grade 0) ===" << std::endl;
    try { Form bad("Bad", 0, 10); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    std::cout << "=== Form: grade too high (exec grade 0) ===" << std::endl;
    try { Form bad("Bad", 10, 0); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    std::cout << "=== Form: grade too low (sign grade 151) ===" << std::endl;
    try { Form bad("Bad", 151, 10); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    std::cout << "=== Form: grade too low (exec grade 151) ===" << std::endl;
    try { Form bad("Bad", 10, 151); }
    catch (std::exception& e) { std::cout << "Caught: " << e.what() << std::endl; }

    // ── beSigned: grade high enough ──────────────────────────────────────────
    std::cout << std::endl << "=== beSigned: bureaucrat grade sufficient ===" << std::endl;
    try {
        Bureaucrat senior("Senior", 10);
        Form permit("Work Permit", 50, 50);
        std::cout << "Before: " << permit;
        permit.beSigned(senior);
        std::cout << "After:  " << permit;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    // ── beSigned: grade too low ──────────────────────────────────────────────
    std::cout << "=== beSigned: bureaucrat grade insufficient ===" << std::endl;
    try {
        Bureaucrat junior("Junior", 100);
        Form clearance("Security Clearance", 25, 5);
        clearance.beSigned(junior);
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    // ── signForm: success ────────────────────────────────────────────────────
    std::cout << std::endl << "=== signForm: success ===" << std::endl;
    try {
        Bureaucrat boss("Boss", 1);
        Form memo("Internal Memo", 5, 3);
        boss.signForm(memo);
        std::cout << memo;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    // ── signForm: failure ────────────────────────────────────────────────────
    std::cout << "=== signForm: failure ===" << std::endl;
    try {
        Bureaucrat intern("Intern", 149);
        Form restricted("Classified", 10, 5);
        intern.signForm(restricted);
        std::cout << restricted;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    // ── Form OCF: copy constructor ───────────────────────────────────────────
    std::cout << std::endl << "=== Form OCF: copy constructor ===" << std::endl;
    try {
        Bureaucrat worker("Worker", 1);
        Form original("Original", 50, 50);
        worker.signForm(original);             // sign the original
        Form copy(original);                   // copy constructor
        std::cout << "Original: " << original;
        std::cout << "Copy:     " << copy;     // copy should also be signed
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    // ── Form OCF: copy assignment ────────────────────────────────────────────
    std::cout << "=== Form OCF: copy assignment (transfers isSigned only) ===" << std::endl;
    try {
        Bureaucrat worker("Worker", 1);
        Form a("FormA", 50, 50);
        Form b("FormB", 50, 50);
        worker.signForm(a);
        std::cout << "a before assign: " << a;
        std::cout << "b before assign: " << b;
        b = a;  // copies isSigned; name/grades stay as FormB's
        std::cout << "b after b=a:     " << b;
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