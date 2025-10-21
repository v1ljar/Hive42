#pragma once

#include <iostream>
#include <string>
#include "contact.hpp"

class PhoneBook{
	private:
		Contact	contacts[8];
		int		index;
	public:
		PhoneBook();
		void add_contact();
		void search_contact() const;
};
