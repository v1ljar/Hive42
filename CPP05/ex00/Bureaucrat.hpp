#pragma once

#include <iostream>
#include <exception>

class Bureaucrat
{
	private:
		const std::string _name;
		int	_grade;

	public:
		Bureaucrat();
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();

		// Exceptions
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const throw() {return "Grade is too high!";} 
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw() { return "Grade is too low!";}
		};

		// Getters
		const std::string& getName() const;
		int	getGrade() const;

		// Member functions
		void increment_grade();
		void decrement_grade();
};
std::ostream& operator<<(std::ostream& output, const Bureaucrat& bur);