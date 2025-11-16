// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Dog.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:32 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:33 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << _type << " default constructor called." << std::endl;
	std::cout << "Dog ";
	_brain = new Brain();
}

Dog::Dog(std::string type): Animal(type)
{
	std::cout << _type << " parametrized constructor called." << std::endl;
	std::cout << "Dog ";
	_brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << _type << " copy constructor called." << std::endl;
	_brain = new Brain(*other._brain);
}

Dog& Dog::operator=(const Dog& other)
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
