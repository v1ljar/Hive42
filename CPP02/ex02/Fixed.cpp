#include "Fixed.hpp"

Fixed::Fixed() : _value(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int nbr)
{
	// std::cout << "Int constructor called" << std::endl;
	_value = nbr * (1 << _nbr_frac_bits);
}

Fixed::Fixed(const float float_nbr)
{
	// std::cout << "Float constructor called" << std::endl;
	_value = static_cast<int>(roundf(float_nbr * (1 << _nbr_frac_bits)));
}

Fixed::Fixed(const Fixed &other) 
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed &other)
{
	// std::cout << "Copy assigment constructor called" << std::endl;
	if (this != &other)
		this->_value = other.getRawBits();
	return *this;
}

Fixed::~Fixed()
{
	// std::cout << "Destructor called" << std::endl;
}

/*
 * Comparison operators
*/

bool Fixed::operator>(const Fixed &other) const
{
	return bool(toFloat() > other.toFloat());
}

bool Fixed::operator<(const Fixed &other) const
{
	return bool(toFloat() < other.toFloat());
}

bool Fixed::operator>=(const Fixed &other) const
{
	return bool(toFloat() >= other.toFloat());
}

bool Fixed::operator<=(const Fixed &other) const
{
	return bool(toFloat() <= other.toFloat());
}

bool Fixed::operator==(const Fixed &other) const
{
	return bool(toFloat() == other.toFloat());
}

bool Fixed::operator!=(const Fixed &other) const
{
	return bool(toFloat() != other.toFloat());
}

/*
 * Arithmetic operators
*/

Fixed Fixed::operator+(const Fixed &other) const
{
	return Fixed(toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const
{
	return Fixed(toFloat() - other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const
{
	return Fixed(toFloat() / other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const
{
	return Fixed(toFloat() * other.toFloat());
}

/*
 * Increment/decrement operators
*/

Fixed& Fixed::operator++()
{
	_value++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed	temp = *this;

	_value++;
	return (temp);
}

Fixed& Fixed::operator--()
{
	_value--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed	temp = *this;

	_value--;
	return (temp);
}

/*
 * Min/max member functions
*/

Fixed& Fixed::min(Fixed &one, Fixed &two)
{
	return (one > two ? two : one);
}

const Fixed& Fixed::min(const Fixed &one, const Fixed &two)
{
	return (one > two ? two : one);
}

Fixed& Fixed::max(Fixed &one, Fixed &two)
{
	return (one > two ? one : two);
}

const Fixed& Fixed::max(const Fixed &one, const Fixed &two)
{
	return one.toFloat() > two.toFloat() ? one : two;
}

/*
 * Utils
*/

int Fixed::getRawBits( void ) const
{
	// std::cout << "getRawBits member function called" << std::endl;
	return this->_value;
}

void Fixed::setRawBits( int const raw )
{
	// std::cout << "setRawBits member function called" << std::endl;
	this->_value = raw;
	return ;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _nbr_frac_bits));
}

int		Fixed::toInt(void) const
{
	return (_value / (1 << _nbr_frac_bits));
}

/*
 * Overload of the insertion («) operator
*/

std::ostream& operator<<(std::ostream& output, const Fixed &nbr)
{
	output << nbr.toFloat();
	return output;
}