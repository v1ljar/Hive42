
#include "iter.hpp"
#include <iostream>

int uppp(int c)
{
	return ++c;
}

int main( void ) {
	int array[] = { 'a', 2, 3 };
	const int len = 3;

	::iter(&array, len, uppp);
	for (int i = 0; i < len; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
