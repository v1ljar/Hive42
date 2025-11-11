#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	_brain = new Brain();
	std::cout << _type << " default constructor called." << std::endl;
}

Dog::Dog(std::string type): Animal(type)
{
	_brain = new Brain();
	std::cout << _type << " parametrized constructor called." << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	*this = other;
	std::cout << _type << " copy constructor called." << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		Animal::operator=(other);
		delete _brain;
		_brain = new Brain(*other._brain);
	}
	std::cout << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog ";
	delete _brain;
	std::cout << _type << " destructor called." << std::endl;
}

void Dog::makeSound() const
{
	std::cout << _type << " says auh-auh-auh" << std::endl;
}
