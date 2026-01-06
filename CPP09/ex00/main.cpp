
#include "BitcoinExchange.hpp"

#include <ctime>
#include <iomanip>
#include <string>
#include <chrono>

void check_file_existance(char *input, BitcoinExchange& data);
bool is_valid_date(std::string date);

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
	while(std::getline(datafile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ',');
		getline(ss, rate);
		if (is_valid_date(date)) {
			std::tm time = {};
			std::istringstream strstream(date.c_str());
			strstream >> std::get_time(&time, "%Y-%m-%d");
			std::setprecision(10);
			double _rate = strtod(rate.c_str(), nullptr);
			time_t _time = mktime(&time);
			data._data.insert({_time, _rate});
		}
	}
	for (auto x: data._data) {
		std::cout << ctime(&x.first) << " " << std::setprecision(12) << x.second << "\n";
	}
	datafile.close();
}

bool is_valid_date(std::string _date) {
	struct tm tm = {};
	return strptime(_date.c_str(), "%Y-%m-%d", &tm);
}