// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanB.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:09:28 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:09:31 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name) {};

void	HumanB::attack()
{
	if (weapon)
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
	else
		std::cout << name << " has no weapon!" << std::endl;
}

void	HumanB::setWeapon(Weapon &club)
{
	weapon = &club;
}
