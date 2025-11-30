// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Form.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/24 10:30:22 by vuljas            #+#    #+#             //
//   Updated: 2025/11/24 10:30:22 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("DefaultForm"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "Default constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

Form::Form(const std::string& name, const int gradeToSign, const int	gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToExecute < 1 || gradeToSign < 1)
		throw GradeTooHighException();
	if (gradeToExecute > 150 || gradeToSign > 150)
		throw GradeTooLowException();
	std::cout << "Parametrized constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

Form::Form(const Form& other)
	: _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Copy constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

Form::~Form()
{
	std::cout << "Destructor called! [ Name: " << _name << " ]" << std::endl;
}

// Exceptions
const char* Form::GradeTooHighException::what() const noexcept
{
	return "Form grade too high!";
}

const char* Form::GradeTooLowException::what() const noexcept
{
	return "Form grade too low!";
}

const char* Form::FormIsSignedException::what() const noexcept
{
	return "Form is already signed!";
}

// Getters
const std::string& Form::getName() const
{
	return _name;
}

bool Form::getIsSigned() const
{
	return _isSigned;
}

int Form::getGradeToSign() const
{
	return _gradeToSign;
}

int Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

// Member functions
void Form::beSigned(const Bureaucrat& bur)
{
	if (bur.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	if (_isSigned)
		throw FormIsSignedException();
	_isSigned = true;
}

std::ostream& operator<<(std::ostream& output, const Form& f)
{
	output << f.getName() << ", form is signed: " << (f.getIsSigned() ? "True" : "False")
		<< ", grade to sign: " << f.getGradeToSign()
		<< ", grade to execute: " << f.getGradeToExecute() << ".";
	return output;
}
