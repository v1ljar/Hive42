// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:08:22 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:08:26 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>

int	main()
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "\t\t\t[ Memory addresses ]\n"
			  << "\t\t String variable: " << &str
			  << "\n\t\t       stringPTR: " << stringPTR
			  << "\n\t\t       stringREF: " << &stringREF
			  << std::endl;

	std::cout << "\n\t\t\t     [ Values ]\n"
			  << "\t\t String variable: " << str
			  << "\n\t\t       stringPTR: " << *stringPTR
			  << "\n\t\t       stringREF: " << stringREF
			  << std::endl;
	return (0);
}
