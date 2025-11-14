// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Dog.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:15:07 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:15:08 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain*	_brain;
	public:
		Dog();
		Dog(std::string type);
		Dog(const Dog& other);
		Dog& operator=(const Dog& other);
		~Dog();
		void makeSound() const override;
};
