// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Base.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:36:47 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:36:48 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>

class Base
{
	public:
		virtual ~Base() = default;

};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);
