// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   contact.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/23 13:22:49 by vuljas            #+#    #+#             //
//   Updated: 2025/10/23 13:22:54 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "contact.hpp"

Contact::Contact() {}

std::string	get_input(const std::string& prompt)
{
	std::string	input;

	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, input))
		{
			std::cout << "\t\t[ EOF detected in get_input. Exiting the program! ]\n";
			std::exit(0);
		}
		if (!input.empty())
			return input;
		std::cout << "\t\t[ Please insert valid value! ]\n";
	}
}

void Contact::fill() {
	first_name = get_input("\t\t Enter first name: ");
	last_name = get_input("\t\t  Enter last name: ");
	nickname = get_input("\t\t   Enter nickname: ");
	phone_number = get_input("\t       Enter phone number: ");
	darkest_secret = get_input("\t     Enter darkest secret: ");
}

std::string	Contact::get_first_name() const{
	return first_name;
}

std::string	Contact::get_last_name() const{
	return last_name;
}

std::string	Contact::get_nickname() const{
	return nickname;
}

std::string	Contact::get_phone_number() const{
	return phone_number;
}

std::string	Contact::get_darkest_secret() const{
	return darkest_secret;
}
