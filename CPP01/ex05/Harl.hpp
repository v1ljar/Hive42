// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Harl.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:11:59 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:12:00 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <string>
#include <iostream>

class Harl{
	private:
		void debug( void );
		void info( void );
		void warning( void );
		void error( void );
	public:
		Harl();
		~Harl();
		void complain( std::string level );
};
