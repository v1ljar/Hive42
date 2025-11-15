// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cat.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:40 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:40 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << _type << " default constructor called." << std::endl;
	std::cout << "Cat ";
	_brain = new Brain();
}

Cat::Cat(std::string type): Animal(type)
{
	std::cout << _type << " parametrized constructor called." << std::endl;
	std::cout << "Cat ";
	_brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << _type << " copy constructor called." << std::endl;
	_brain = new Brain(*other._brain);
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << _type << " copy assignment operator called." << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete _brain;
		_brain = new Brain(*other._brain);
	}
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
