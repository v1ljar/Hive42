// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Brain.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:44 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:44 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <string>
#include <iostream>

class Brain
{
	protected:
		std::string	_ideas[100];
	public:
		Brain();
		Brain(const Brain& other);
		Brain& operator=(const Brain& other);
		~Brain();
};
