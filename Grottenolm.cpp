#include "Grottenolm.hpp"

// ── Orthodox Canonical Form ──────────────────────────────────────────────────

Grottenolm::Grottenolm()
{
}

Grottenolm::Grottenolm(const Grottenolm& other)
{
    *this = other;
}

Grottenolm& Grottenolm::operator=(const Grottenolm& other)
{
    if (this != &other)
    {
        // TODO: copy members
    }
    return *this;
}

Grottenolm::~Grottenolm()
{
}

// ── Member operators ─────────────────────────────────────────────────────────

bool Grottenolm::operator==(const Grottenolm& other) const
{
    // TODO
}

bool Grottenolm::operator!=(const Grottenolm& other) const
{
    // TODO
}

bool Grottenolm::operator>(const Grottenolm& other) const
{
    // TODO
}

void* Grottenolm::operator*(void* rhs) const
{
    // TODO
}

void* Grottenolm::operator++()
{
    // TODO
}

void* Grottenolm::operator++(int)
{
    // TODO
}

// ── Non-member operators ─────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Grottenolm& obj)
{
    // TODO
}
