#include "PmergeMe.hpp"

int main(int ac, char **av) {
	if (ac == 1) {
		std::cerr << "Program requires a positive integer sequence as an argument!\n";
		return (1);
	}

	PmergeMe master;
	try {
		master.check_args_fill(ac, av);
		master.print_before();
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return (2);
	}
	return (0);
}