#include "contact.hpp"
#include "phonebook.hpp"

int	main()
{
	PhoneBook pb;
	std::string choice;

	std::cout << "\n\t\tWelcome to phonebook\n" << std::endl;
	std::cout << "Please insert one of the commands: ADD, SEARCH or EXIT" << std::endl;
	std::cout << "Your choice: ";
	if (!choice.compare("ADD"))
	{
		Contact::fill;
	}
	// std::cin >> choice;
	// std::cout << choice << std::endl;
	return (0);
}