// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Weapon.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:08:56 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:09:03 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <string>
#include <iostream>

class Weapon{
	private:
		std::string type;
	public:
		Weapon();
		Weapon(std::string type);
		const std::string & getType();
		void setType(std::string type);
};
