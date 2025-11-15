// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Animal.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:15:36 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:15:36 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
	_type = other._type;
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
	std::cout << "Animal " << _type << " makes general Animal sound." << std::endl;
}
