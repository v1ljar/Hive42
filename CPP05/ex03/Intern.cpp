#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Intern Default constructor called!" << std::endl;
}

Intern::Intern(const Intern& other)
{
	(void)other;
	std::cout << "Intern Copy constructor called!" << std::endl;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	std::cout << "Intern Copy assignment operator called!" << std::endl;
	return *this;
}

Intern::~Intern()
{
	std::cout << "Intern Destructor called!" << std::endl;
}

const char*Intern::ParametersNotValidException::what() const noexcept
{
	return "Intern parameters not valid!";
}

AForm* Intern::makeForm(const std::string& name, const std::string& target) const
{
	if (name.empty() || target.empty())
		throw ParametersNotValidException();
	std::string _name = name;
	for (size_t i = 0; i < name.length(); i++)
		_name[i] = std::tolower(name[i]);
	std::string formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm* (*ctors[3])(const std::string&) = {
		[](const std::string& t) -> AForm* { return new ShrubberyCreationForm(t); },
		[](const std::string& t) -> AForm* { return new RobotomyRequestForm(t); },
		[](const std::string& t) -> AForm* { return new PresidentialPardonForm(t); }
	};

	for (int i = 0; i < 3; i++) {
		if (_name == formNames[i]) {
			std::cout << "Intern creates " << formNames[i] << std::endl;
			return ctors[i](target);
		}
}
	std::cout << "Intern could not find the form: " << name << std::endl;
	return nullptr;
}