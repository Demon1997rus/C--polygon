#pragma once

#include <iostream>

namespace rdi {

class Point {
public:
    Point();
    Point(int x, int y);
    ~Point();

    void setX(int x);
    void setY(int y);
    int &rx();
    int &ry();
    int x() const;
    int y() const;
    bool isNull() const;

    Point &operator*=(float factor);
    Point &operator*=(double factor);
    Point &operator*=(int factor);
    Point &operator+=(const Point &other);
    Point &operator-=(const Point &other);
    Point &operator/=(double divisor);

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);

private:
    int m_x;
    int m_y;
};
} // namespace rdi
