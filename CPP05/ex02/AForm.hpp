#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool	_isSigned;
		const int	_gradeToSign;
		const int	_gradeToExecute;

	public:
		AForm();
		AForm(const std::string& _name, const int _gradeToSign, const int	_gradeToExecute);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other) = delete;
		virtual ~AForm() = 0;

		// Exceptions
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const throw() {return "AForm grade too high!";}
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw() {return "AForm grade too low!";}
		};
		class FormNotSignedException : public std::exception {
			public:
				const char* what() const throw() {return "AForm is not signed!";}
		};

		// Getters
		const std::string& getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		// Member functions
		virtual void beSigned(const Bureaucrat& bur);
		virtual void execute(Bureaucrat const & executor) const;
};
// Overload insertion operator (<<)
std::ostream& operator<<(std::ostream& output, const AForm& f);
