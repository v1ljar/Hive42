// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Weapon.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:09:47 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:09:50 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Weapon.hpp"

Weapon::Weapon() {};
Weapon::Weapon(std::string type) : type(type) {};

const std::string & Weapon::getType()
{
	return type;
}

void Weapon::setType(std::string type)
{
	Weapon::type = type;
}
