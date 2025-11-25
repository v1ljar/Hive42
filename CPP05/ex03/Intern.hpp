#pragma once

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern& other) = delete;
		Intern& operator=(const Intern& other) = delete;
		~Intern();
		class FormNameNoExistException : std::exception
		{
			public:
				const char* what() const throw() {return "Form name does not exist!";};
		};
		
};