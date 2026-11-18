#include "Point.hpp"

Point::Point(void) : _x(0), _y(0)
{
}

Point::Point(const float x, const float y) : _x(x), _y(y)
{
}

Point::Point(const Point &other) : _x(other._x), _y(other._y)
{
}

/* _x and _y are const: once a Point is built they can never change,
   so there is nothing this operator is allowed to copy. It exists to
   respect the Orthodox Canonical Form and just returns *this. */
Point	&Point::operator=(const Point &other)
{
	(void)other;
	return (*this);
}

Point::~Point(void)
{
}

Fixed	Point::getX(void) const
{
	return (_x);
}

Fixed	Point::getY(void) const
{
	return (_y);
}
