#pragma once

#include <iostream>
#include <chrono>
#include <exception>
#include <vector>
#include <deque>
#include <limits.h>

class PmergeMe {
	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();

		void check_args_fill(int ac, char **av);
		void print_before();
};