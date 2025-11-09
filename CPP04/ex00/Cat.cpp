#include "Cat.hpp"

Cat::Cat(): Animal("Cat"), _type("Cat")
{
	std::cout << _type << " default constructor called." << std::endl;
}

Cat::Cat(std::string type): Animal(type), _type("Cat")
{
	std::cout << _type << " parametrized constructor called." << std::endl;
}

Cat::Cat(const Cat& other)
{
	*this = other;
	std::cout << _type << " copy constructor called." << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
		_type = other._type;
	std::cout << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout << _type << " destructor called." << std::endl;
}
