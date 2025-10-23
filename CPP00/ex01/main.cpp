// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/23 13:23:15 by vuljas            #+#    #+#             //
//   Updated: 2025/10/23 13:23:19 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "contact.hpp"
#include "phonebook.hpp"

int	main()
{
	PhoneBook pb;
	std::string choice;

	std::cout << "\n\t\t\tWelcome to phonebook" << std::endl;
	while (true)
	{
		std::cout << "\nPlease insert one of the commands: ADD, SEARCH or EXIT\n" \
				  << "\t\t      Your choice: ";
		if (!std::getline(std::cin, choice))
		{
			if (std::cin.eof())
			{
				std::cin.clear();
				std::cout << "\n[ EOF detected. Exiting the program! ]\n";
				std::exit(0);
			}
		}
		if (choice == "ADD")
			pb.add_contact();
		else if (choice == "SEARCH")
			pb.search_contact();
		else if (choice == "EXIT")
		{
			std::cout << "\n\t\t\t See you next time!" << std::endl;
			break ;
		}
		else
			std::cout << "\t\t[ Please enter a valid command ]" << std::endl;
	}
	return (0);
}
