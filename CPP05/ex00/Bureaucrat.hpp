#pragma once

#include <iostream>
#include <exception>

class Bureaucrat
{
	private:
		std::string _name;
		int	_grade;
	public:
		Bureaucrat() = delete;
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();
		// Exceptions
		class GradeTooHighException{};
		class GradeTooLowException{};
		// Getters
		const std::string& getName();
		int	getGrade();
		// Member functions
		void increment_grade();
		void decrement_grade();
};
std::ostream& operator<<(std::ostream& output, Bureaucrat& bur);