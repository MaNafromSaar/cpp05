#ifndef TELETUBBY_HPP
#define TELETUBBY_HPP


// ===== Auto-generated Orthodox Canonical Form (adjust placeholders as needed) =====

class Teletubby
{
private:
    // NOTE: Add meaningful private members here.

public:
    Teletubby();
    Teletubby(const Teletubby& other);
    Teletubby& operator=(const Teletubby& other);
    ~Teletubby();

    // NOTE: Placeholder signatures — update types/semantics to match real behavior.
    bool operator==(const Teletubby& other) const;
    bool operator!=(const Teletubby& other) const;
    bool operator>(const Teletubby& other) const;
    void* operator++();          // TODO: choose meaningful return type
    void* operator++(int);       // TODO: choose meaningful return type
};

// Non-member operators (free functions — cannot be class members):
// NOTE: <ostream> (or <iostream>) must be included for std::ostream.
std::ostream& operator<<(std::ostream& os, const Teletubby& obj); // TODO: implement in .cpp
// NOTE: <istream> (or <iostream>) must be included for std::istream.
std::istream& operator>>(std::istream& is, Teletubby& obj); // TODO: implement in .cpp
// ===== End auto-generated block =====
#endif
