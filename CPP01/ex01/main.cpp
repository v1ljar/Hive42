// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:05:58 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:06:04 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

int	main()
{
	Zombie	*crew;
	int		N;

	N = 5;
	crew = zombieHorde(N, "Liina");
	for (int i = 0; i < N; i++)
	{
		crew[i].announce();
	}
	delete[] crew;
	return (0);
}
