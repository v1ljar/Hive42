// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   contact.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/23 13:23:04 by vuljas            #+#    #+#             //
//   Updated: 2025/10/23 13:23:08 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <string>

class Contact{
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	phone_number;
		std::string	darkest_secret;
	public:
		Contact();
		void 		fill();
		std::string	get_first_name() const;
		std::string	get_last_name() const;
		std::string	get_nickname() const;
		std::string	get_phone_number() const;
		std::string	get_darkest_secret() const;
};
