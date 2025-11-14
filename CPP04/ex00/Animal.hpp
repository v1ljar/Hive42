// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Animal.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:14:16 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:14:17 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>

class Animal
{
	protected:
		std::string	_type;
	public:
		Animal();
		Animal(const std::string type);
		Animal(const Animal& other);
		Animal& operator=(const Animal& other);
		virtual ~Animal();
		std::string getType() const;
		virtual void makeSound() const;
};
