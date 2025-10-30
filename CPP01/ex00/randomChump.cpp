// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   randomChump.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:06:51 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:06:56 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

void randomChump( std::string name )
{
	Zombie	zomb(name);

	zomb.announce();
}
