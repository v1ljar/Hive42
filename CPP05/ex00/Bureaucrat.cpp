#include "Bureaucrat.hpp"
#include <string>

Bureaucrat::Bureaucrat() : _name("Intern"), _grade(150)
{
	std::cout << "Default constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	if (_grade > 150)
		throw GradeTooLowException();
	else if (_grade < 1)
		throw GradeTooHighException();
	std::cout << "Parametrized constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
	std::cout << "Copy constructor called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		_grade = other._grade;
	}
	std::cout << "Copy assignment operator called! [ Name: " << _name << "; Grade: " << _grade << " ]" << std::endl;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called! [ Name: " << _name << " ]" << std::endl;
}

const std::string& Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

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

std::ostream& operator<<(std::ostream& output, const Bureaucrat& bur)
{
	output << bur.getName() << ", bureaucrat grade " << bur.getGrade() << ".";
	return output;
}
