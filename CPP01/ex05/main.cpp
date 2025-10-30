// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:12:14 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:12:15 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Harl.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "\tProgram accepts only 1 argument!\n"
				  << "\tValid arguments: DEBUG, INFO, WARNING, ERROR"
				  << std::endl;
		return (1);
	}

	Harl	harl;

	harl.complain(av[1]);
	return 0;
}
