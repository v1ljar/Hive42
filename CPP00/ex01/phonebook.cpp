#include "phonebook.hpp"
#include <iomanip>

PhoneBook::PhoneBook() : index(0) {}

void	PhoneBook::add_contact()
{
	if (index >= 8)
		index = 0;
	contacts[index].fill();
	index++;
}

void	PhoneBook::search_contact() const
{
	if (index == 0)
	{
		std::cout << "\t\tNo contacts found." << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First name" << "|";
	std::cout << std::setw(10) << "Last name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < index; i++)
	{
		std::cout	<< std::setw(10) << i + 1 << "|"
					<< std::setw(10) << contacts[i].get_first_name().substr(0, 10) << "|"
					<< std::setw(10) << contacts[i].get_last_name().substr(0, 10) << "|"
					<< std::setw(10) << contacts[i].get_nickname().substr(0, 10) << std::endl;
	}
}