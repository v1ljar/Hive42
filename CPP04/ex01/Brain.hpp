#pragma once

#include <string>
#include <iostream>

class Brain
{
	protected:
		std::string	_ideas[100];
	public:
		Brain();
		Brain(const Brain& other);
		Brain& operator=(const Brain& other);
		~Brain();
};