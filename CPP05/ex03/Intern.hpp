#pragma once

#include <iostream>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		class ParametersNotValidException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};

		AForm* makeForm(const std::string& name, const std::string& target) const;
};