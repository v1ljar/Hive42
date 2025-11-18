#include "Bureaucrat.hpp"
#include <string>

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	std::cout << _name << " Parametrized constructor called!" << std::endl;
	if (_grade > 150)
		throw GradeTooLowException();
	else if (_grade < 1)
		throw GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade)
{
	std::cout << _name << " Copy constructor called!" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		_name = other._name;
		_grade = other._grade;
	}
	std::cout << _name << " Copy assignment operator called!" << std::endl;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << _name << " Destructor called!" << std::endl;
}

class Bureaucrat::GradeTooHighException : public std::exception
{
	public:
		const char* what() const throw() {
			return "Grade is too high!";
		} 
};

class Bureaucrat::GradeTooLowException : public std::exception
{
	public:
		const char* what() const throw() {
			return "Grade is too low!";
		}
};

const std::string& Bureaucrat::getName()
{
	return _name;
}

int Bureaucrat::getGrade()
{
	return _grade;
}

void Bureaucrat::increment_grade()
{
	_grade--;
	if (_grade > 150)
		std::cerr << "Grade too low!" << std::endl;
	else if (_grade < 1)
		std::cerr << "Grade too high!" << std::endl;
}

void Bureaucrat::decrement_grade()
{
	_grade++;
	if (_grade > 150)
		std::cerr << "Grade too low!" << std::endl;
	else if (_grade < 1)
		std::cerr << "Grade too high!" << std::endl;
}

std::ostream& operator<<(std::ostream& output, Bureaucrat& bur)
{
	output << bur.getName() << ", bureaucrat grade " << bur.getGrade() << "." << std::endl;
	return output;
}
