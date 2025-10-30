// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   zombieHorde.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:05:24 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:05:29 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

Zombie::Zombie() {}

Zombie* zombieHorde( int N, std::string name )
{
	Zombie	*horde;
	
	horde = new Zombie[N];
	for (int i = 0; i < N; i++)
	{
		horde[i].setName(name);
	}
	return (horde);
}
