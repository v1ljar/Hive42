// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Base.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:36:52 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:36:52 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>

Base* generate(void)
{
	Base* res;
	
	int	randint = rand() % 3 + 1;
	switch (randint)
	{
		case (1):
		{
			res = new A();
			std::cout << "Generated object A\n";
			break;
		}
		case (2):
		{
			res = new B();
			std::cout << "Generated object B\n";
			break;
		}
		case (3):
		{
			res = new C();
			std::cout << "Generated object C\n";
			break;
		}
	}
	return (res);
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Pointer identified: A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "Pointer identified: B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "Pointer identified: C\n";
	else
		std::cout << "Pointer identified failed: Unknown type\n";
}

void identify(Base& p)
{
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Reference identified: A\n";
		return ;
	} catch (...) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Reference identified: B\n";
		return ;
	} catch (...) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "Reference identified: C\n";
		return ;
	} catch (...) {}

	std::cout << "Reference identified failed: Unknown type\n";
}
