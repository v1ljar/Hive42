#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << _type << " default constructor called." << std::endl;
}

Dog::Dog(std::string type): Animal(type)
{
	std::cout << _type << " parametrized constructor called." << std::endl;
}

Dog::Dog(const Dog& other)
{
	*this = other;
	std::cout << _type << " copy constructor called." << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other)
		_type = other._type;
	std::cout << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout << _type << " destructor called." << std::endl;
}

void Dog::makeSound() const
{
	std::cout << _type << " says auh-auh-auh" << std::endl;
}
