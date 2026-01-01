#pragma once

#include <stack>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		MutantStack() = default;
		MutantStack(const MutantStack& other) {
			return *this;
		};
		MutantStack& operator=(const MutantStack& other) {
			if (this != &other) {
				
			}
		};
		~MutantStack() = default;

		// Member functions
};
