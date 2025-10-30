// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:07:41 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:07:45 by vuljas           ###   ########.fr       //
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
