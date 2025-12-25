// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   whatever.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/25 15:46:30 by vuljas            #+#    #+#             //
//   Updated: 2025/12/25 15:46:31 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>

template<typename T>
void swap(T& first, T& second)
{
	T	temp = first;

	first = second;
	second = temp;
}

template<typename T>
T& min(T& first, T& second)
{
	if (first < second)
		return first;
	else
		return second;
}

template<typename T>
T& max(T& first, T& second)
{
	if (first > second)
		return first;
	else
		return second;
}
