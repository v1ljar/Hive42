
#include "Span.hpp"
#include <iostream>

int main( void ) {
	Span sp = Span(5);

	sp.addNumber(1);
	sp.addNumber(2);
	sp.addNumber(3);
	sp.addNumber(4);
	sp.addNumber(5);
	sp.addNumber(6);
	for (auto i : sp._data)
	{
		std::cout << i << " ";
	}
	std::cout << "\n" << sp.longestSpan() << std::endl;
	return 0;
}
