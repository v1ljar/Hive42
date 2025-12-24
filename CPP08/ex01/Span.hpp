#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

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

		// Member functions
		void addNumber(unsigned int nbr);
		int longestSpan();
		int shortestSpan();
		void addMultipleNumbers();
};
