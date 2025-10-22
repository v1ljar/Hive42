#include "phonebook.hpp"

PhoneBook::PhoneBook() : index(0), total(0) {}
void	print_full_contact(const Contact contacts[8]);

void	PhoneBook::add_contact()
{
	if (index >= 8)
		index = 0;
	contacts[index].fill();
	index++;
	total++;
}

std::string	get_correct_value(std::string str)
{
	if (str.size() > 10)
		return str.substr(0, 9) + ".";
	else
		return str;
}

void	PhoneBook::search_contact() const
{
	if (total == 0)
	{
		std::cout << "\t\t[ No contacts found. ]" << std::endl;
		return ;
	}
	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First name" << "|";
	std::cout << std::setw(10) << "Last name" << "|";
	std::cout << std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < 8 && i < total; i++)
	{
		std::cout	<< std::setw(10) << i + 1 << "|"
					<< std::setw(10) << get_correct_value(contacts[i].get_first_name()) << "|"
					<< std::setw(10) << get_correct_value(contacts[i].get_last_name()) << "|"
					<< std::setw(10) << get_correct_value(contacts[i].get_nickname()) << std::endl;
	}
	print_full_contact(contacts);
}

void	print_full_contact(const Contact contacts[8])
{
	std::cout << "For full information of a contact, enter index: ";
	std::string	indx;
	if (!std::getline(std::cin, indx))
		{
			std::cout << "\t\t[ EOF detected in get_input. Exiting the program! ]\n";
			std::exit(0);
		}
	if (indx.size() == 1 && (indx[0] >= '1' && indx[0] <= '8'))
	{
		int	casted_i = indx[0] - '1';
		std::cout	<< contacts[casted_i].get_first_name() << std::endl
					<< contacts[casted_i].get_last_name() << std::endl
					<< contacts[casted_i].get_nickname() << std::endl
					<< contacts[casted_i].get_phone_number() << std::endl
					<< contacts[casted_i].get_darkest_secret() << std::endl;
	}
	else
		std::cout << "\t\t[ '" << indx << "' is not a valid index! ]" << std::endl;
}