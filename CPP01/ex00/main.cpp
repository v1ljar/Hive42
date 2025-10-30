// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:07:25 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:07:29 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

int	main()
{
	Zombie	zomb("Zombie 1");
	Zombie	*zom_new;

	std::cout << "\t\t[ class Zombie and member function announce ]" << std::endl;
	zomb.announce();
	std::cout << "\n\t\t[ functions: newZombie and randomChump ]" << std::endl;
	randomChump("Zombie 2.1");
	zom_new = newZombie("Zombie 2.2");
	zom_new->announce();
	delete zom_new;
	return (0);
}
