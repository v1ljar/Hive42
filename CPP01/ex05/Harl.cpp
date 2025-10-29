#include "Harl.hpp"

Harl::Harl() {};
Harl::~Harl() {};

void Harl::complain( std::string level )
{
	enum	Level var = INVALID;

	if (level == "DEBUG")
		var = DEBUG;
	else if (level == "INFO")
		var = INFO;
	else if (level == "WARNING")
		var = WARNING;
	else if (level == "ERROR")
		var = ERROR;

	switch (var)
	{
	case DEBUG:
	{
		Harl::debug();
		break;
	}
	case INFO:
	{
		Harl::info();
		break;
	}
	case WARNING:
	{
		Harl::warning();
		break;
	}
	case ERROR:
	{
		Harl::error();
		break;
	}
	default:
		break;
	}
}

void Harl::debug(void)
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void)
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}