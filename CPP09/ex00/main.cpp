// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/01/31 14:27:03 by vuljas            #+#    #+#             //
//   Updated: 2026/01/31 14:27:04 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	BitcoinExchange data;

	if (ac != 2) {
		std::cerr << "Program requires 1 argument (the input file)." << "\n";
		return (1);
	}
	try {
		data.check_file_existance_fill_data(av[1], data);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return (1);
	}

	std::ifstream infile;
	infile.open(av[1]);
	if (!infile) {
		std::cerr << "Failed to open the input file.\n";
		return (1);
	}
	std::string line;
	std::string date;
	std::string value;
	std::string delimiter;

	std::getline(infile, line);
	if (line != "date | value") {
		infile.close();
		std::cerr << "Error: infile must start with line: `date | value`\n";
		return (2);
	}
	while (std::getline(infile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ' ');
		if (data.is_valid_date(date) && !ss.eof()) {
			getline(ss, delimiter, ' ');
			if (delimiter != "|")
				std::cerr << "Error: bad input => '|' is missing.\n";
			else {
				if (ss.eof())
					std::cerr << "Error: bad input => value is missing.\n"; 
				else {
					getline(ss, value);
					try {
						double _value = data.convert_nbr(value, true);
						time_t _time = data.convert_time(date);
						
						auto it = data._data.lower_bound(_time);
						if (it == data._data.end())
							--it;
						else if (it->first != _time) {
							if (it == data._data.begin())
								throw std::runtime_error("Error: date is out of scope: " + date);
							--it;
						}
						std::cout << date << " => " << _value << " = " << _value * it->second << "\n";
					} catch (std::exception& e) {
						std::cerr << e.what() << "\n";
					}
				}
			}
		}
		else
			std::cerr << "Error: bad input => " << date << "\n"; 
	}
	infile.close();
	return 0;
}
