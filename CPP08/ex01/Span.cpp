#include "Span.hpp"

void check_space(const int _filled, const int _size)
{
	if (!(_filled < _size))
		throw std::out_of_range("Array is full!");
}

Span::Span(unsigned int nbr) : _size(nbr), _filled(0), _data({}) {}

void Span::addNumber(unsigned int nbr) {
	try {
		check_space(_filled, _size);
	} catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << "\n";
		return ;
	}
	_data.insert(_data.begin() + _filled++, nbr);
}