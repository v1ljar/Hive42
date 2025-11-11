#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat ";
	Brain	*brain_ptr;

	brain_ptr = new Brain();
	_brain = brain_ptr;
	std::cout << _type << " default constructor called." << std::endl;
}

Cat::Cat(std::string type): Animal(type)
{
	Brain	*brain_ptr;

	brain_ptr = new Brain();
	_brain = brain_ptr;
	std::cout << _type << " parametrized constructor called." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	*this = other;
	std::cout << _type << " copy constructor called." << std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		_type = other._type;
		_brain = other._brain;
	}
	std::cout << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat ";
	delete _brain;
	std::cout << _type << " destructor called." << std::endl;
}

void Cat::makeSound() const
{
	std::cout << _type << " says mjäu-mjäu-mjäu" << std::endl;
}
