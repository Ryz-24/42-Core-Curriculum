#include "Fixed.hpp"
#include <cmath>

const int	Fixed::_fractionalBits = 8;

/* ---------- Orthodox Canonical Form ---------- */

Fixed::Fixed(void) : _rawBits(0)
{
}

Fixed::Fixed(const int n) : _rawBits(n * (1 << _fractionalBits))
{
}

Fixed::Fixed(const float f) : _rawBits(static_cast<int>(roundf(f * (1 << _fractionalBits))))
{
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		this->_rawBits = other._rawBits;
	return (*this);
}

Fixed::~Fixed(void)
{
}

/* ---------- raw bits and conversions ---------- */

int	Fixed::getRawBits(void) const
{
	return (this->_rawBits);
}

void	Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}

float	Fixed::toFloat(void) const
{
	return ((float)this->_rawBits / (1 << _fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (this->_rawBits / (1 << _fractionalBits));
}

/* ---------- comparison: same scale, so compare raw values ---------- */

bool	Fixed::operator>(const Fixed &other) const
{
	return (this->_rawBits > other._rawBits);
}

bool	Fixed::operator<(const Fixed &other) const
{
	return (this->_rawBits < other._rawBits);
}

bool	Fixed::operator>=(const Fixed &other) const
{
	return (this->_rawBits >= other._rawBits);
}

bool	Fixed::operator<=(const Fixed &other) const
{
	return (this->_rawBits <= other._rawBits);
}

bool	Fixed::operator==(const Fixed &other) const
{
	return (this->_rawBits == other._rawBits);
}

bool	Fixed::operator!=(const Fixed &other) const
{
	return (this->_rawBits != other._rawBits);
}

/* ---------- arithmetic ---------- */

Fixed	Fixed::operator+(const Fixed &other) const
{
	Fixed	result;

	result.setRawBits(this->_rawBits + other._rawBits);
	return (result);
}

Fixed	Fixed::operator-(const Fixed &other) const
{
	Fixed	result;

	result.setRawBits(this->_rawBits - other._rawBits);
	return (result);
}

/* raw * raw has the scale twice (256 * 256): divide once by 256.
   The product is done in a long so it can't overflow an int first. */
Fixed	Fixed::operator*(const Fixed &other) const
{
	Fixed	result;
	long	product;

	product = static_cast<long>(this->_rawBits) * other._rawBits;
	result.setRawBits(static_cast<int>(product / (1 << _fractionalBits)));
	return (result);
}

/* raw / raw cancels the scale: multiply by 256 BEFORE dividing.
   Dividing by zero crashes, which the subject accepts. */
Fixed	Fixed::operator/(const Fixed &other) const
{
	Fixed	result;
	long	scaled;

	scaled = static_cast<long>(this->_rawBits) * (1 << _fractionalBits);
	result.setRawBits(static_cast<int>(scaled / other._rawBits));
	return (result);
}

/* ---------- increment / decrement by epsilon (one raw step = 1/256) ---------- */

Fixed	&Fixed::operator++(void)
{
	this->_rawBits++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	old(*this);

	this->_rawBits++;
	return (old);
}

Fixed	&Fixed::operator--(void)
{
	this->_rawBits--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	old(*this);

	this->_rawBits--;
	return (old);
}

/* ---------- min / max ---------- */

Fixed	&Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed	&Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed	&Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed	&Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

/* ---------- output ---------- */

std::ostream	&operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return (out);
}
