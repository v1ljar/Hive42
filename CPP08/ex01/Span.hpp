#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

class Span {
	private:
		
		unsigned int _size;
		unsigned int _filled;

	public:
		std::vector<int> _data;
		Span() = delete;
		Span(unsigned int nbr);
		Span(const Span* other) = delete;
		Span& operator=(const Span* other) = delete;
		~Span() = default;

		void addNumber(unsigned int nbr);
};
