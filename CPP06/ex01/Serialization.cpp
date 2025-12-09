// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Serialization.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:35:46 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:35:47 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Serialization.hpp"

uintptr_t Serialization::serialize(Data* ptr)
{
	return (reinterpret_cast<intptr_t>(ptr));
}

Data* Serialization::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}
