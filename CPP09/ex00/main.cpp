
#include "BitcoinExchange.hpp"

#include <ctime>
#include <iomanip>
#include <string>
#include <chrono>

void check_file_existance(char *input, BitcoinExchange& data);
bool is_valid_date(std::string date);
time_t convert_time(std::string& date);
double convert_nbr(std::string& snbr);

int main(int ac, char **av)
{
	BitcoinExchange data;

	if (ac != 2) {
		std::cout << "Program requires 1 argument (the input file)." << "\n";
		return (1);
	}
	try {
		check_file_existance(av[1], data);
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
	}

	std::ifstream infile;
	infile.open(av[1]);
	std::string line;
	std::string date;
	std::string value;
	std::string delimiter;

	std::getline(infile, line);
	while (std::getline(infile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ' ');
		if (is_valid_date(date) && !ss.eof()) {
			getline(ss, delimiter, ' ');
			if (delimiter != "|")
				std::cout << "Error: bad input => '|' is missing.\n";
			else {
				if (ss.eof()) {
					std::cout << "Error: bad input => value is missing.\n"; 
				}
				else {
					getline(ss, value);
					try {
						double _value = convert_nbr(value);
						time_t _time = convert_time(date);
						
						auto it = data._data.find(_time);
						if (it == data._data.end()) 
							it = data._data.lower_bound(_time);
						if (it != data._data.end()) {
							std::cout << date << " => " << _value << " = " << _value * it->second << "\n";
						}
						else
							std::cout << "Error: cannot find the value for date: " << _time << "\n";
					} catch (std::exception& e) {
						std::cout << e.what() << "\n";
					}
				}
			}
		}
		else
			std::cout << "Error: bad input => " << date << "\n"; 
	}
	infile.close();
	return 0;
}

void check_file_existance(char *input, BitcoinExchange& data) {
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
	
	std::getline(datafile, line);
	while (std::getline(datafile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ',');
		getline(ss, rate);
		if (is_valid_date(date)) {
			try {
				double _rate = convert_nbr(rate);
				data._data.insert({convert_time(date), _rate});
			}catch (...) {}				
		}
	}
	// for (auto x: data._data) {
	// 	std::cout << ctime(&x.first) << " " << std::setprecision(12) << x.second << "\n";
	// }
	datafile.close();
}

bool is_valid_date(std::string _date) {
	struct tm tm = {};
	return strptime(_date.c_str(), "%Y-%m-%d", &tm);
}

time_t convert_time(std::string& date) {
	std::tm time = {};
	std::istringstream strstream(date.c_str());
	strstream >> std::get_time(&time, "%Y-%m-%d");
	time_t _time = mktime(&time);
	return (_time);
}

double convert_nbr(std::string& snbr) {
	char* end;
	double _rate = strtod(snbr.c_str(), &end);

	if (!*end && (_rate >= 0 && _rate <= 2147483647))
		return (_rate);
	else if (_rate < 0)
		throw std::runtime_error("Error: not a positive number.");
	else if (_rate > 2147483647)
		throw std::runtime_error("Error: too large a number.");
	else
		throw std::runtime_error("Error: Number is not valid.");
}
