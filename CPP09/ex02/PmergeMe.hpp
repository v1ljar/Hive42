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
		~PmergeMe() = default;

		// ------------- Getters
		const std::vector<int>& get_vec() const;
		const std::deque<int>& get_deq() const;

		// ------------- Helper functions
		void check_args_fill(int ac, char **av);
		void print_before();

		template <typename T>
		T fordJohnson(const T& data){
			size_t len = data.size();
			if (len <= 1)
				return data;

			std::vector<std::pair<int,int>> pairs;
			bool has_odd = len % 2 != 0;
			int odd_value = 0;

			for (size_t i = 0; i + 1 < len; i += 2) {
				int a = data[i];
				int b = data[i + 1];

				if (a > b)
					std::swap(a, b);
				pairs.push_back(std::make_pair(a, b));
			}
			if (has_odd)
				odd_value = data[len - 1];

			T big;
			for (size_t i = 0; i < pairs.size(); i++) {
				big.push_back(pairs[i].second);
			}

			T main_chain = fordJohnson(big);

			for (size_t i = 0; i < pairs.size(); i++) {
				int value = pairs[i].first;
				size_t low = 0;
				size_t high = main_chain.size();

				while (low < high) {
					size_t mid = (low + high) / 2;

					if (main_chain[mid] < value)
						low = mid + 1;
					else
						high = mid;
				}
				main_chain.insert(main_chain.begin() + low, value);
			}
			if (has_odd) {
				size_t low = 0;
				size_t high = main_chain.size();

				while (low < high) {
					size_t mid = (low + high) / 2;

					if (main_chain[mid] < odd_value)
						low = mid + 1;
					else
						high = mid;
				}
				main_chain.insert(main_chain.begin() + low, odd_value);
			}
			return main_chain;
		}
};