// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/02/12 10:38:10 by vuljas            #+#    #+#             //
//   Updated: 2026/02/12 10:38:12 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error! Usage: ./RPN <inverted Polish mathematical expression>\n";
		return (1);
	}
	RPN master;
	std::string line(av[1]);

	try {
		master.check_argv(line);
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
		return (2);
	}

	try {
		master.process_data(line);
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
		return (2);
	}
	return (0);
}
