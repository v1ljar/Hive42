#include "RPN.hpp"

RPN::RPN() : _data() {}

RPN::RPN(const RPN& other) : _data(other._data) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_data.clear();
		for (auto x : other._data) {
			_data.push_back(x);
		}
	}
	return *this;
}

RPN::~RPN() {}