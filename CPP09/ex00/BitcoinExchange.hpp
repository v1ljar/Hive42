#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <filesystem>
#include <map>

/*
	Convert the parsed date to a time_t value time_t date = mktime(&tm);
*/

class BitcoinExchange {
	public:
		std::map<time_t, double> _data;
};
