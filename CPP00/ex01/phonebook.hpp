// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   phonebook.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/23 13:23:50 by vuljas            #+#    #+#             //
//   Updated: 2025/10/23 13:23:53 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "contact.hpp"

class PhoneBook{
	private:
		Contact	contacts[8];
		int		index;
		int		total;
	public:
		PhoneBook();
		void add_contact();
		void search_contact() const;
};
