#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm parametrized constructor called!"
			  << "\n\t[ Target: " << _target << ". (toSign: 145 | toExecute: 137) ]"
			  << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm Destructor called!" << std::endl;
}

void ShrubberyCreationForm::execute(const Bureaucrat & executor) const
{
	if (executor.getGrade() > getGradeToExecute())
		throw GradeTooHighException();
	if (!getIsSigned())
		throw FormNotSignedException();

	std::ofstream file((_target + "_shrubbery").c_str());
	if (!file.is_open())
		throw std::runtime_error("Failed to open shrubbery file!");
	file << R"(
						 /\
						/  \
					   / OO \
					  / /\OO\
					 / O  /\O\
					/__/__/__\
				   /  OO    OO \
				  / /\OO /\ OO/\ \
				 / O  /\O  O  /\O \
				/__/__/__\__/__/__\
			   /   OO    OO   OO   \
			  / /\OO/\  OO  /\OO/\  \
			 / O  /\O  OOOO  O/\  O  \
			/__/__/__\_/OO\__/__\__/__\
		   /    OO    OOOOOO    OO     \
		  / /\OO/\OO/\ OOOO /\OO/\OO/\ \
		 / O  /\O  OO  OOOO  OO  O/\  O \
		/__/__/__\__/__OO__\__/__/__\__/__\
	   /     OO      OOOOOOOO      OO      \
	  / /\OO/\OO/\OO/ OOOOOO \OO/\OO/\OO/\ \
	 / O  /\O  OO  OOOO OO OOOO  OO  O/\  O \
	/__/__/__\__/__/__OOOO__\__/__/__\__/__/__\
						 ||
						 ||
	)";
	file.close();
	std::cout << "ShrubberyCreationForm executed successfully! "
			  << _target << "_shrubbery created and tree saved into it!" << std::endl;
}
