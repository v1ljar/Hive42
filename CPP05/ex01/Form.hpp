#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool	_isSigned;
		const int	_gradeToSign;
		const int	_gradeToExecute;

	public:
		Form();
		Form(const std::string& _name, const int _gradeToSign, const int	_gradeToExecute);
		Form(const Form& other);
		Form& operator=(const Form& other) = delete;
		virtual ~Form();

		// Exceptions
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class FormIsSignedException : public std::exception {
			public:
				const char* what() const noexcept override;
		};

		// Getters
		const std::string& getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		// Member functions
		virtual void beSigned(const Bureaucrat& bur);
};

// Overload insertion operator (<<)
std::ostream& operator<<(std::ostream& output, const Form& f);
