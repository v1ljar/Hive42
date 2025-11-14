// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Cat.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/14 11:16:36 by vuljas            #+#    #+#             //
//   Updated: 2025/11/14 11:16:36 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain*	_brain;
	public:
		Cat();
		Cat(const std::string type);
		Cat(const Cat& other);
		Cat& operator=(const Cat& other);
		~Cat();
		void makeSound() const override;
};
