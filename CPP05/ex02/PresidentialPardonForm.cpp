#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : AForm("PresidentialPardonForm", 25, 5), _target(target)
{
	std::cout << "RobotomyRequestForm parametrized constructor called.\n\t[ Target: "
			  << _target
			  << ". (toSign: 25 | toExecute: 5) ]"
			  << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm Destructor called!\n";
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const
{
	std::cout << "\t\tPresidentialPardonForm execute() called by: " << executor.getName() << ".\n";
	if (executor.getGrade() > getGradeToExecute())
	{
		std::cout << "PresidentialPardonForm failed!\n\t[ Executor: " << executor.getName() << " | Target: " << _target << " ]\n";
		throw Bureaucrat::GradeTooLowException();
	}
	if (!getIsSigned())
	{
		std::cout << "PresidentialPardonForm failed!\n\t[ Executor: " << executor.getName() << " | Target: " << _target << " ]\n";
		throw FormNotSignedException();
	}
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox!\n";

}
