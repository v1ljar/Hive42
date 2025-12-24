
#include "Span.hpp"

int main()
{
	srand(time(0));
	std::cout << "\n--- [ Test1: test from the subject ] ---\n";
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << "\n--- [ Test2: add element to a full array ] ---\n";
	sp.addNumber(1);

	std::cout << "\n--- [ Test3: array with 10 000 numbers and use addMultipleNumbers to fill it ] ---\n";
	Span sp2 = Span(10000);
	sp2.addNumber(-1);
	sp2.addMultipleNumbers();
	std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;
	std::cout << "Longest span: " << sp2.longestSpan() << std::endl;
	return 0;
}