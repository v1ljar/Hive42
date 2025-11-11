#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << _type << " default constructor called." << std::endl;
}

WrongCat::WrongCat(std::string type): WrongAnimal(type)
{
	std::cout << _type << " parametrized constructor called." << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	*this = other;
	std::cout << _type << " copy constructor called." << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if (this != &other)
		_type = other._type;
	std::cout << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << _type << " destructor called." << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << _type << " makes sound mjäu" << std::endl;
}
