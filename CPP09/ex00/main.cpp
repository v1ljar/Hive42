
#include "BitcoinExchange.hpp"

#include <ctime>
#include <iomanip>
#include <string>

void check_file_existance(char *input, BitcoinExchange& data);

int main(int ac, char **av)
{
	BitcoinExchange data;

	if (ac != 2) {
		std::cout << "Program requires 1 argument (the input file)!" << "\n";
		return (1);
	}
	try {
		check_file_existance(av[1], data);
	} catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << "\n";
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
		throw std::runtime_error("Input file is empty!");
	}

	datafile.open("data.csv");
	if (!datafile)
		throw std::runtime_error("No data file!");
	if (std::filesystem::is_empty("data.csv")) {
		datafile.close();
		throw std::runtime_error("Data file is empty!");
	}
	std::string line;
	std::string date;
	std::string rate;
	
	std::getline(datafile, line);
	while(std::getline(datafile, line)) {
		std::istringstream ss(line);
		getline(ss, date, ',');

		getline(ss, rate);
		std::cout << "date: " << date << " | " << rate << "\n";
		std::tm time;
		std::istringstream strstream(date.c_str());
		strstream >> std::get_time(&time, "%Y-%m-%d");

		data._data.insert({mktime(&time), rate});
	}
	// for (auto x: data._data) {
	// 	std::cout << x.first << " " << x.second << "\n";
	// }

	datafile.close();
}