#pragma once

template <typename T>
class MutantStack {
	private:
		unsigned int _size;
		unsigned int _filled;
		
	public:
		std::vector<int> _data;
		MutantStack() = delete;
		MutantStack(unsigned int nbr);
		MutantStack(const MutantStack* other) = delete;
		MutantStack& operator=(const MutantStack* other) = delete;
		~MutantStack() = default;

		// Member functions
		void addNumber(unsigned int nbr);
		int longestSpan();
		int shortestSpan();
		void addMultipleNumbers();
};
