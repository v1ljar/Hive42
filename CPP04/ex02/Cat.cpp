#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat ";
	_brain = new Brain();
	std::cout << _type << " default constructor called." << std::endl;
}

Cat::Cat(std::string type): Animal(type)
{
	std::cout << "Cat ";
	_brain = new Brain();
	std::cout << _type << " parametrized constructor called." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other)
{
	_brain = new Brain(*other._brain);
	std::cout << _type << " copy constructor called." << std::endl;
}

Cat& Cat::operator=(const Cat& other)
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
