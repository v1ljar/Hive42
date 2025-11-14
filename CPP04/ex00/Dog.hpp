// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Dog.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:14:00 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:14:00 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		Dog(std::string type);
		Dog(const Dog& other);
		Dog& operator=(const Dog& other);
		~Dog();
		void makeSound() const override;
};
