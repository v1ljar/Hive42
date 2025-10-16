#pragma once

#include <iostream>
#include <string>

class Contact{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	darkest_secret;
	public:
		
};

class PhoneBook{
	public:
		Contact *contacts[8];
};
