// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bureaucrat.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/24 10:30:30 by vuljas            #+#    #+#             //
//   Updated: 2025/11/24 10:30:31 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"
#include <string>

Bureaucrat::Bureaucrat() : _name("Intern"), _grade(150)
{
	std::cout << "Bureaucrat Default constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	if (_grade > 150)
		throw GradeTooLowException();
	else if (_grade < 1)
		throw GradeTooHighException();
	std::cout << "Bureaucrat Parametrized constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
	std::cout << "Bureaucrat Copy constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		_grade = other._grade;
	}
	std::cout << "Bureaucrat Copy assignment operator called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat Destructor called! [ Name: " << _name << " ]" << std::endl;
}

// Exceptions

const char* Bureaucrat::GradeTooHighException::what() const noexcept
{
	return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const noexcept
{
	return "Grade is too low!";
}

// Getters
const std::string& Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

// Member functions
void Bureaucrat::increment_grade()
{
	if (_grade <= 1)
		throw GradeTooHighException();
	_grade--;
}

void Bureaucrat::decrement_grade()
{
	if (_grade >= 150)
		throw GradeTooLowException();
	_grade++;

}

void Bureaucrat::signForm(Form& form)
{
	try {
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << std::endl;
	} catch (Form::GradeTooLowException& e){
		std::cout << _name << " couldn’t sign " << form.getName()
				  << " because " << e.what() << "." << std::endl;
	}
}

// Overload operator (<<)
std::ostream& operator<<(std::ostream& output, const Bureaucrat& bur)
{
	output << bur.getName() << ", bureaucrat grade " << bur.getGrade() << ".";
	return output;
}
