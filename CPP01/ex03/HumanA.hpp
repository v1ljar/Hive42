// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanA.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:09:34 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:09:37 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Weapon.hpp"

class HumanA{
	private:
		std::string	name;
		Weapon		&weapon;
	public:
		HumanA(std::string name, Weapon &weapon);
		void		attack();
};
