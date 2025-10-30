// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:06:36 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:06:44 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <string>

class Zombie{
	private:
		std::string	name;
	public:
		Zombie(std::string name);
		~Zombie();
		void announce( void );
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );
