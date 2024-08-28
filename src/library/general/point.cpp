#include "point.h"

namespace rdi {

Point::Point() : Point(0, 0) {}

Point::Point(int x, int y) : m_x(x), m_y(y) {}

Point::~Point() {}

void Point::setX(int x)
{
    m_x = x;
}

void Point::setY(int y)
{
    m_y = y;
}

int &Point::rx()
{
    return m_x;
}

int &Point::ry()
{
    return m_y;
}

int Point::x() const
{
    return m_x;
}

int Point::y() const
{
    return m_y;
}

bool Point::isNull() const
{
    return (m_x == 0 && m_y == 0);
}

Point &Point::operator*=(float factor)
{
    m_x *= factor;
    m_y *= factor;
    return *this;
}

Point &Point::operator*=(double factor)
{
    m_x *= factor;
    m_y *= factor;
    return *this;
}

Point &Point::operator*=(int factor)
{
    m_x *= factor;
    m_y *= factor;
    return *this;
}

Point &Point::operator+=(const Point &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

Point &Point::operator-=(const Point &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

Point &Point::operator/=(double divisor)
{
    m_x /= divisor;
    m_y /= divisor;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "x = " << rhs.m_x << " "
       << "y = " << rhs.m_y;
    return os;
}
} // namespace rdi
