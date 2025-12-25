// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/25 15:47:01 by vuljas            #+#    #+#             //
//   Updated: 2025/12/25 15:47:01 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
	const size_t len = 3;

	std::cout << "Original array: ";
	::iter(array, len, print<int>);
	std::cout << std::endl;

	std::cout << "Iterated array: ";
	::iter(array, len, inc<int>);
	::iter(array, len, print<int>);
	std::cout << std::endl;

	std::cout << "\n--- [ Test2: character array and function toupper ] ---\n";
	char arr[] = { 'a', 'b' , 'y', 'z'};
	const size_t siz = 4;

	std::cout << "Original array: ";
	::iter(arr, siz, print<char>);
	std::cout << std::endl;

	::iter(arr, siz, to_upper);
	std::cout << "Iterated array: ";
	::iter(arr, siz, print<char>);
	std::cout << std::endl;

	std::cout << "\n--- [ Test3: const array and print function ] ---\n";
	const int array2[] = { 11, 22, 33, 44, 55 };
	const size_t len2 = 5;

	std::cout << "Const array: ";
	::iter(array2, len2, print<int>);
	std::cout << std::endl;
	return 0;
}
