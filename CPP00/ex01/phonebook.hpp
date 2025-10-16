#pragma once

#include <iostream>
#include <string>

class Contact{
	public:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
	private:
		std::string	phone_number;
		std::string	darkest_secret;
};

class PhoneBook{
	public:
		Contact *contacts[8];
};
