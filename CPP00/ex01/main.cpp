#include "contact.hpp"
#include "phonebook.hpp"

int	main()
{
	PhoneBook pb;
	std::string choice;

	std::cout << "\n\t\tWelcome to phonebook\n" << std::endl;
	while (true)
	{
		std::cout << "Please insert one of the commands: ADD, SEARCH or EXIT" << std::endl;
		std::cout << "Your choice: ";
		std::getline(std::cin, choice);
		if (choice == "ADD")
			pb.add_contact();
		else if (choice == "SEARCH")
			pb.search_contact();
		else if (choice == "EXIT")
		{
			std::cout << "See you next time!" << std::endl;
			break ;
		}
		else
			std::cout << "Please enter a valid command" << std::endl;
	}
	return (0);
}