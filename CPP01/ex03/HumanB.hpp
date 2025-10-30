// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanB.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:09:22 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:09:25 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Weapon.hpp"

class HumanB{
	private:
		std::string	name;
		Weapon		*weapon;
	public:
		HumanB(std::string name);
		void	attack();
		void	setWeapon(Weapon &club);
};
