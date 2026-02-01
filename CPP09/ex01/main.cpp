#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error! Usage: ./RPN <inverted Polish mathematical expression>\n";
		return (1);
	}
	RPN master;

	for (int i = 0; av[1][i] != '\0';) {
		if (av[1][i + 1] != ' ' && av[1][i + 1] != '\0') {
			std::cerr << "Error\n";
			return (2);
		}
		master._data.push_back(av[1][i]);
		if (av[1][i + 1] == '\0')
			break;
		else
			i += 2;
	}

	for (auto x : master._data) {
		std::cout << x << " ";
	}
	std::cout << "\n";
	return (0);
}