#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("DefaultAForm"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "AForm Default constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

AForm::AForm(const std::string& name, const int gradeToSign, const int	gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (gradeToExecute < 1 || gradeToSign < 1)
		throw GradeTooHighException();
	if (gradeToExecute > 150 || gradeToSign > 150)
		throw GradeTooLowException();
	std::cout << "AForm Parametrized constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

AForm::AForm(const AForm& other)
	: _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "AForm Copy constructor called!\n\t[ Name: " << _name
		<< ", is signed: " << (_isSigned ? "True" : "False") << ", grade to sign: " << _gradeToSign
		<< ", grade to execute: " << _gradeToExecute << ". ]" << std::endl;
}

AForm::~AForm()
{
	std::cout << "AForm Destructor called! [ Name: " << _name << " ]" << std::endl;
}

// Getters
const std::string& AForm::getName() const
{
	return _name;
}

bool AForm::getIsSigned() const
{
	return _isSigned;
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

// Member functions
void AForm::beSigned(const Bureaucrat& bur)
{
	if (bur.getGrade() > _gradeToSign)
		throw Bureaucrat::GradeTooLowException();
	_isSigned = true;
}

void AForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > _gradeToExecute)
		throw GradeTooHighException();
	if (!_isSigned)
		throw FormNotSignedException();
	std::cout << "AForm execution ready to call!" << std::endl;
}

std::ostream& operator<<(std::ostream& output, const AForm& f)
{
	output << f.getName() << ", AForm is signed: " << (f.getIsSigned() ? "True" : "False")
		<< ", grade to sign: " << f.getGradeToSign()
		<< ", grade to execute: " << f.getGradeToExecute() << ".";
	return output;
}
