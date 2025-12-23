
#include "easyfind.hpp"
#include <iostream>

int main( void ) {
	std::cout << "--- [ Test1: valid array, occurence found ] ---\n";
	std::vector<int> array = { 'a', 1, 2, 3, 'a'};

	try {
		::easyfind(array, 'a');
	} catch (std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- [ Test2: valid array, no occurence found ] ---\n";
	try {
		::easyfind(array, 'b');
	} catch (std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- [ Test3: empty array ] ---\n";
	std::vector<int> arr = {};
	try {
		::easyfind(arr, 'b');
	} catch (std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}
