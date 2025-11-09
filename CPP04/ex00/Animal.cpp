#include "Animal.hpp"

Animal::Animal() : _type("Default")
{
	std::cout << "Animal " << _type << " default constructor called." << std::endl;
}

Animal::Animal(const std::string type) : _type(type)
{
	std::cout << "Animal " << _type << " parametrized constructor called." << std::endl;
}

Animal::Animal(const Animal& other)
{
	*this = other;
	std::cout << "Animal " << _type << " copy constructor called." << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
		_type = other._type;
	std::cout << "Animal " << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal " << _type << " destructor called." << std::endl;
}

std::string Animal::getType() const
{
	return (_type);
}

void Animal::makeSound() const
{
	if (_type == "Dog")
		std::cout << "Estonian " << _type << " says auh-auh-auh" << std::endl;
	else if (_type == "Cat")
		std::cout << "Estonian " << _type << " says mjau-mjau-mjau" << std::endl;
}
