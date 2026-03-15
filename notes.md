# C++ Module 05 Notes

This file explains common terms used in this project.

## Exception

An exception is a C++ object used to signal an error or invalid state.

- You throw it when something is wrong.
- You catch it where you want to handle the error.

Example from this project:
- Grade out of range throws GradeTooHighException or GradeTooLowException.
- Executing an unsigned form throws FormNotSignedException.

Why useful:
- Keeps error handling separate from normal logic.
- Avoids returning error codes everywhere.

## Abstract Class

An abstract class is a class that cannot be instantiated directly.

It has at least one pure virtual function, for example:
- virtual void executeAction() const = 0;

In this project:
- AForm is abstract.
- Concrete forms (ShrubberyCreationForm, RobotomyRequestForm, PresidentialPardonForm) inherit from AForm and implement executeAction().

Why useful:
- Enforces a common interface.
- Lets you work with base pointers/references (polymorphism).

## Switch

switch chooses one code path from many based on an integer-like key.

Typical form:
- switch (key) { case X: ...; break; default: ...; }

In C++98, switch does not work directly on std::string.
You can still use switch by converting text to a key first (for example, from the first 3 chars).

Why useful:
- Cleaner than many if/else checks in some cases.

## Factory

A factory is a function/class whose job is to create objects.

In this project:
- Intern::makeForm(formName, target) acts as a factory.
- It decides which concrete form to create and returns AForm*.

Why useful:
- Centralizes object creation.
- Caller depends on AForm interface, not concrete types.

## Interface

An interface is the set of public functions a class exposes.

In C++, this is often represented by an abstract base class with pure virtual methods.

In this project:
- AForm acts as the interface for all form types.
- Code can call beSigned() and execute() without needing to know the concrete form.

Why useful:
- Defines a clear contract for derived classes.
- Makes code easier to extend and test.

## Base Pointer

A base pointer is a pointer to a base class type that can point to derived objects.

Example in this project:
- AForm* ptr = new RobotomyRequestForm("Bender");

This lets one pointer type handle many concrete classes.
When calling virtual methods through the base pointer, C++ picks the derived implementation at runtime.

Why useful:
- Enables polymorphism.
- Keeps APIs generic while behavior stays specific.

## Random via Time

Pseudo-random choices can be derived from current time values.

In RobotomyRequestForm, a simple approach is:
- read current time (for example, tv_usec)
- compute tv_usec % 2
- map result to success/failure (roughly 50/50)

Notes:
- This is not cryptographic randomness.
- For exercise behavior, it is practical and simple.

## Extra Terms

### OCF (Orthodox Canonical Form)

For these modules, classes typically implement:
- default constructor
- copy constructor
- copy assignment operator
- destructor

### Polymorphism

Polymorphism means one base type can refer to many derived objects.

Example:
- AForm* can point to ShrubberyCreationForm, RobotomyRequestForm, or PresidentialPardonForm.

The correct executeAction() is chosen at runtime.
