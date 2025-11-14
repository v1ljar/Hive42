// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Brain.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:15:28 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:15:28 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called." << std::endl;
}

Brain::Brain(const Brain& other)
{
	*this = other;
	std::cout << "Brain copy constructor called." << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
			_ideas[i] = other._ideas[i];
	}
	std::cout << "Brain copy assignment operator called." << std::endl;
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called." << std::endl;
}
