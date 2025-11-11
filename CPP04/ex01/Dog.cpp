#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Dog ";
	Brain	*brain_ptr;

	brain_ptr = new Brain();
	_brain = brain_ptr;
	std::cout << _type << " default constructor called." << std::endl;
}

Dog::Dog(std::string type): Animal(type)
{
	Brain	*brain_ptr;

	brain_ptr = new Brain();
	_brain = brain_ptr;
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
		_type = other._type;
		_brain = other._brain;
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
