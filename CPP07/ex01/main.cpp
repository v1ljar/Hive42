
#include "iter.hpp"
#include <iostream>

template <typename T>
void inc(T& x) {
	++x;
}

template <typename T>
void print(const T&x) {
	std::cout << x << " ";
}

void to_upper(char& c) {
	c = static_cast<char>(std::toupper(c));
}

int main( void ) {
	std::cout << "--- [ Test1: integer array and function to increment the integer by 1 ] ---\n";
	int array[] = { 'a', 2, 3 };
	const int len = 3;

	std::cout << "Original array: ";
	::iter(array, len, print<int>);
	std::cout << std::endl;

	std::cout << "Iterated array: ";
	::iter(array, len, inc<int>);
	::iter(array, len, print<int>);
	std::cout << std::endl;

	std::cout << "\n--- [ Test2: character array and function toupper ] ---\n";
	char arr[] = { 'a', 'b' , 'y', 'z'};
	const int siz = 4;

	std::cout << "Original array: ";
	::iter(arr, siz, print<char>);
	std::cout << std::endl;

	::iter(arr, siz, to_upper);
	std::cout << "Iterated array: ";
	::iter(arr, siz, print<char>);
	std::cout << std::endl;
	return 0;
}
