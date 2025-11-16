// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:25 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:25 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "\t[ Given tests ]" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n\t[ Cleanup destructors ]" << std::endl;
	delete j;//should not create a leak
	delete i;

	std::cout << "\t[ More tests with array of Animal objects ]" << std::endl;
	std::cout << "\t\t[ Constructors ]" << std::endl;
	int	nbr = 4;
	int n;
	Animal*	animals[nbr];

	for (n = 0; n < nbr; n++)
	{
		if (n < nbr / 2)
			animals[n] = new Dog();
		else
			animals[n] = new Cat();
	}
	std::cout << "\t\t[ Destructors ]" << std::endl;
	for (n = 0; n < nbr; n++)
		delete animals[n];
	// std::cout << "\t\t[ Test to instaniate pure virtual Animal class ]" << std::endl;
	// Animal* animal = new Animal();
	return 0;
}
