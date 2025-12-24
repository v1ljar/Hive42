#include "Span.hpp"
#include <numeric>

void check_space(const int _filled, const int _size)
{
	if (!(_filled < _size))
		throw std::out_of_range("Array is full!");
}

void check_elements(const int filled) {
	if (filled < 2)
		throw std::length_error("Not enough elements to find a span!");
}

int find_difference(std::vector<int> data) {
	std::sort(data.begin(), data.end());
	std::adjacent_difference(data.begin(), data.end(), data.begin());
	data.erase(data.begin());
	return (*std::min_element(data.begin(), data.end()));
}

int generateRandomNumber() {
	return (rand() % 10000);
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

int Span::shortestSpan() {
	try {
		check_elements(_filled);
	} catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	return (find_difference(_data));
}

void Span::addMultipleNumbers() {
	unsigned int data_size = _data.size();
	if (data_size == _size) {
		std::cout << "Data is full, nothing to add!\n";
		return ;
	}
	std::cout << "Before adding multiple numbers, data size is: " << data_size << "\n";
	_data.insert(_data.begin() + data_size, _size, 0);
	std::fill(_data.begin() + data_size, _data.begin() + _size, rand());
	_filled = _size;
	std::cout << "After adding multiple numbers, data size is: " << _data.size() << "\n";
}
