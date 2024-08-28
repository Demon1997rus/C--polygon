#ifndef LEXCASTCUSTOMTYPE_H
#define LEXCASTCUSTOMTYPE_H

#include <iostream>
#include <stdexcept>

class LexCastCustomType {
    unsigned short m_number;

public:
    explicit LexCastCustomType(unsigned short number = 0) : m_number(number) {}

    // ...
    unsigned short value_without_sign() const { return m_number; }
};

inline std::ostream &operator<<(std::ostream &os, const LexCastCustomType &example)
{
    return os << '-' << example.value_without_sign();
}

inline std::istream &operator>>(std::istream &is, LexCastCustomType &example)
{
    char ch;
    is >> ch;
    if (ch != '-') {
        throw std::logic_error("LexCastCustomType class stores ONLY negative values");
    }
    unsigned short s;
    is >> s;
    example = LexCastCustomType(s);
    return is;
}

#endif // LEXCASTCUSTOMTYPE_H
