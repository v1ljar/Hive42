// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   BitcoinExchange.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/01/31 14:26:57 by vuljas            #+#    #+#             //
//   Updated: 2026/01/31 14:26:59 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "BitcoinExchange.hpp"

// ------------------------- Constructor/destructor
BitcoinExchange::BitcoinExchange() : _data({}) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_data = other._data;
	return *this;
}

// ------------------------- Helper functions
void BitcoinExchange::check_file_existance_fill_data(char *input, BitcoinExchange& data) {
	std::ifstream infile;
	std::ifstream datafile;

	infile.open(input);
	if (!infile)
		throw std::runtime_error("No input file!");
	infile.close();
	if (std::filesystem::is_empty(input)) {
		infile.close();
		throw std::runtime_error("Input file is empty.");
	}

	datafile.open("data.csv");
	if (!datafile)
		throw std::runtime_error("No data file!");
	if (std::filesystem::is_empty("data.csv")) {
		datafile.close();
		throw std::runtime_error("Data file is empty.");
	}

	std::string line;
	std::string date;
	std::string rate;
	
	/* Fill data */
	std::getline(datafile, line);
	if (line != "date,exchange_rate") {
		datafile.close();
		throw std::runtime_error("Data file must start with line: `date,exchange_rate`");
	}
	while (std::getline(datafile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ',');
		getline(ss, rate);
		if (is_valid_date(date)) {
			try {
				double _rate = convert_nbr(rate, false);
				data._data.insert({convert_time(date), _rate});
			} catch (...) {}
		}
	}
	datafile.close();
	if (data._data.empty())
		throw std::runtime_error("No valid dates.");
}

bool BitcoinExchange::is_valid_date(std::string date) {
	if (date.empty())
		return false;

	struct tm tm = {};
	if (!strptime(date.c_str(), "%Y-%m-%d", &tm))
		return false;
	if (date.length() != 10)
		return false;
	if ((tm.tm_mon == 3 || tm.tm_mon == 5 || tm.tm_mon == 8 || tm.tm_mon == 10) && tm.tm_mday > 30)
		return false;
	if (tm.tm_mon == 1) {
		int year = tm.tm_year + 1900;
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			if (tm.tm_mday == 29)
				return false;
			else
				if (tm.tm_mday > 28)
					return false;
		}
	}
	return true;
}

time_t BitcoinExchange::convert_time(std::string& date) {
	std::tm time = {};
	time.tm_hour = 0;
	time.tm_min = 0;
	time.tm_sec = 0;
	std::istringstream strstream(date.c_str());
	strstream >> std::get_time(&time, "%Y-%m-%d");
	time_t _time = mktime(&time);
	return (_time);
}


double BitcoinExchange::convert_nbr(std::string& snbr, bool input_value) {
	char* end;
	double _rate = strtod(snbr.c_str(), &end);

	if (!*end && ((_rate >= 0 && _rate <= INT_MAX && !input_value) || (_rate >= 0 && _rate <= 1000 && input_value)))
		return (_rate);
	else if (_rate < 0)
		throw std::runtime_error("Error: not a positive number.");
	else if (_rate > 1000)
		throw std::runtime_error("Error: too large a number.");
	else
		throw std::runtime_error("Error: Number is not valid.");
}
