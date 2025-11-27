#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm(target, 72, 45), _target(target)
{
	std::cout << "RobotomyRequestForm parametrized constructor called.\n\t[ Target: "
			  << _target
			  << ". (toSign: 72 | toExecute: 45) ]"
			  << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm Destructor called!\n";
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const
{
	std::cout << "\t\tRobotomyRequestForm execute() called by: " << executor.getName() << ".\n";
	std::cout << "***DRILLING noises*** | ***DRILLING noises*** | ***DRILLING noises***\n";
	if (executor.getGrade() > getGradeToExecute())
	{
		std::cout << "Robotomy failed!\n\t[ Executor: " << executor.getName() << " | Target: " << _target << " ]\n";
		throw Bureaucrat::GradeTooLowException();
	}
	if (!getIsSigned())
	{
		std::cout << "Robotomy failed!\n\t[ Executor: " << executor.getName() << " | Target: " << _target << " ]\n";
		throw FormNotSignedException();
	}
	std::cout << _target << " has been robotomized successfully 50% of the time!\n";
}
