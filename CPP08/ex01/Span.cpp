#include "Span.hpp"

void check_space(const int _filled, const int _size)
{
	if (!(_filled < _size))
		throw std::out_of_range("Array is full!");
}

void check_elements(const int filled) {
	if (filled < 2)
		throw std::length_error("Not enough elements to find a span!");
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

int Span::longestSpan() {
	try {
		check_elements(_filled);
	} catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << "\n";
	}
	int max = *std::max_element(_data.begin(), _data.end());
	int min = *std::min_element(_data.begin(), _data.end());
	return (max - min);
}
