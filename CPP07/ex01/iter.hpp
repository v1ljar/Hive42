// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   iter.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/25 15:46:57 by vuljas            #+#    #+#             //
//   Updated: 2025/12/25 15:46:58 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <cstddef>

template<typename A, typename F>
void iter(A* array, const size_t len, F func)
{
	if (!array)
		return ;
	for (size_t i = 0; i < len; i++)
		func(array[i]);
}
