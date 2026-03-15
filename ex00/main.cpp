#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
    std::cout << "--- Valid construction ---" << std::endl;
    try {
        Bureaucrat alice("Alice", 1);
        Bureaucrat bob("Bob", 150);
        Bureaucrat mid("Mid", 75);
        std::cout << alice;
        std::cout << bob;
        std::cout << mid;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << "--- Grade too high: Bureaucrat(\"Bad\", 0) ---" << std::endl;
    try {
        Bureaucrat bad("Bad", 0);
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "--- Grade too low: Bureaucrat(\"Bad\", 151) ---" << std::endl;
    try {
        Bureaucrat bad("Bad", 151);
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "--- Increment at ceiling: Bureaucrat(\"Top\", 1), then ++top ---" << std::endl;
    try {
        Bureaucrat top("Top", 1);
        ++top;
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "--- Decrement at floor: Bureaucrat(\"Bot\", 150), then --bot ---" << std::endl;
    try {
        Bureaucrat bot("Bot", 150);
        --bot;
    }
    catch (std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cout << "--- Prefix increment/decrement: start grade 50 ---" << std::endl;
    try {
        Bureaucrat b("B", 50);
        std::cout << "Start:       " << b;
        ++b;
        std::cout << "After ++b:   " << b;
        --b;
        std::cout << "After --b:   " << b;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << "--- Postfix increment: start grade 50 ---" << std::endl;
    try {
        Bureaucrat b("B", 50);
        std::cout << "Start:        " << b;
        Bureaucrat before = b++;
        std::cout << "Returned b++: " << before;
        std::cout << "b after b++:  " << b;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << "--- Postfix decrement: start grade 50 ---" << std::endl;
    try {
        Bureaucrat b("B", 50);
        std::cout << "Start:        " << b;
        Bureaucrat before = b--;
        std::cout << "Returned b--: " << before;
        std::cout << "b after b--:  " << b;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    std::cout << "--- Copy and assignment ---" << std::endl;
    try {
        Bureaucrat a("A", 10);
        Bureaucrat b(a);
        Bureaucrat c("C", 20);
        std::cout << "a (original):      " << a;
        std::cout << "b (copy of a):     " << b;
        std::cout << "c before assign:   " << c;
        c = a;
        std::cout << "c after c = a:     " << c;
    }
    catch (std::exception& e) {
        std::cout << "Unexpected: " << e.what() << std::endl;
    }

    return 0;
}
/*

Compile with:
c++ -Wall -Wextra -Werror -std=c++98 Bureaucrat.cpp main.cpp -o bureaucrat
*/