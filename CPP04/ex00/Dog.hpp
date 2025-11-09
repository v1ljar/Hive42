#pragma once

#include "Animal.hpp"

class Dog : public Animal
{
	private:
		std::string	_type;
	public:
		Dog();
		Dog(const std::string type);
		Dog(const Dog& other);
		Dog& operator=(const Dog& other);
		~Dog();
};