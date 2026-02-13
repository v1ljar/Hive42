// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   BitcoinExchange.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/01/31 14:26:51 by vuljas            #+#    #+#             //
//   Updated: 2026/01/31 14:26:52 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <filesystem>
#include <map>
#include <ctime>
#include <iterator>
#include <climits>

class BitcoinExchange {
	public:
		// ------------------------- Data container
		std::map<time_t, double> _data;

		// ------------------------- Constructor/destructor
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange() = default;

		// ------------------------- Helper functions
		void check_file_existance_fill_data(char *input, BitcoinExchange& data);
		bool is_valid_date(std::string date);
		time_t convert_time(std::string& date);
		double convert_nbr(std::string& snbr, bool input_value);
};
