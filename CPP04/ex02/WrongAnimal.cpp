// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   WrongAnimal.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:18 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:18 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("Default")
{
	std::cout << "WrongAnimal " << _type << " default constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(const std::string type) : _type(type)
{
	std::cout << "WrongAnimal " << _type << " parametrized constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	_type = other._type;
	std::cout << "WrongAnimal " << _type << " copy constructor called." << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (this != &other)
		_type = other._type;
	std::cout << "WrongAnimal " << _type << " copy assignment operator called." << std::endl;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal " << _type << " destructor called." << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (_type);
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal " << _type << " makes general WrongAnimal sound." << std::endl;
}
