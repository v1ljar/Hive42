#pragma once

#include <iostream>

class Animal
{
	protected:
		std::string	_type;
	public:
		Animal();
		Animal(const std::string type);
		Animal(const Animal& other);
		Animal& operator=(const Animal& other);
		virtual ~Animal() = 0;
		std::string getType() const;
		virtual void makeSound() const;
};