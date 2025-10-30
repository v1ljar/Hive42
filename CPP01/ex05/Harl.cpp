// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Harl.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:12:05 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:12:06 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Harl.hpp"

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug(void)
{
	std::cout << "\t\t[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
	std::cout << "\t\t[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "\t\t[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void)
{
	std::cout << "\t\t[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain( std::string level )
{
	void (Harl::*func_ptrs[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	const std::string	levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			(this->*func_ptrs[i])();
			return ;
		}
	}
	std::cout << "Invalid level!" << std::endl;
}
