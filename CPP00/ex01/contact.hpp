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
		void fill() {};
		std::string	get_first_name() const { return first_name; }
		std::string	get_first_name() const { return last_name; }
		std::string	get_first_name() const { return nickname; }
		std::string	get_first_name() const { return phone_number; }
		std::string	get_first_name() const { return darkest_secret; }
};