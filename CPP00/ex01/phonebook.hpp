#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "contact.hpp"

class PhoneBook{
	private:
		Contact	contacts[8];
		int		index;
		int		total;
	public:
		PhoneBook();
		void add_contact();
		void search_contact() const;
};
