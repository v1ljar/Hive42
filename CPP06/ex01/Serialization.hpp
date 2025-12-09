// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Serialization.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:35:23 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:35:24 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "Data.hpp"
#include <iostream>

class Serialization
{
	private:
		Serialization() = delete;
		Serialization(const Serialization& other) = delete;
		Serialization& operator=(const Serialization& other) = delete;
		~Serialization() = delete;
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};
