// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:37:03 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:37:03 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main()
{
	srand(time(NULL));
	std::cout << "\t\t----- Generating random object -----\n";
	std::cout << "\t\t----- [ First object ] -----\n";
	Base* unos = generate();

	identify(unos);
	identify(*unos);
	delete unos;

	std::cout << "\n\t\t----- [ Second object ] -----\n";
	Base* duos = generate();

	identify(duos);
	identify(*duos);
	delete duos;

	std::cout << "\n\t\t----- [ Third object ] -----\n";
	Base* trios = generate();;

	identify(trios);
	identify(*trios);
	delete trios;

	std::cout << "\n\t\t----- [ Failing object ] -----\n";
	Base fail;

	identify(&fail);
	identify(fail);
	return (0);
}
