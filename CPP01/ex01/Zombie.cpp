// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:05:35 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:05:40 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : name(name) {};

Zombie::~Zombie()
{
	std::cout << name << " has beed destroied by the destructor!" << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << Zombie::name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(std::string setname)
{
	name = setname;
}
