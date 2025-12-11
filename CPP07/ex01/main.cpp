
#include "iter.hpp"
#include <iostream>

int inc(int c)
{
	return ++c;
}

int main( void ) {
	std::cout << "--- [ Test1: integer array and function to increment the integer by 1 ] ---\n";
	int array[] = { 'a', 2, 3 };
	const int len = 3;
	int (*func)(int);

	func = inc;
	std::cout << "Original array: ";
	for (int i = 0; i < len; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << "\nLength: " << len << "\n";
	std::cout << "Iterated array: ";
	::iter(&array, len, func);
	for (int i = 0; i < len; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\n--- [ Test2: character array and function toupper ] ---\n";
	char arr[] = { 'a', 'b' , 'y', 'z'};
	const int siz = 4;

	int (*func2)(int);

	func2 = std::toupper;

	std::cout << "Original array: ";
	for (int i = 0; i < siz; i++) {
		std::cout << arr[i] << " ";
	}
	::iter(&arr, siz, func2);
	std::cout << "\nLength: " << siz << "\n";
	std::cout << "Iterated array: ";
	for (int i = 0; i < siz; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
