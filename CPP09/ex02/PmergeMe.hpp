// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PmergeMe.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/02/12 10:38:46 by vuljas            #+#    #+#             //
//   Updated: 2026/02/12 10:38:48 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
		std::vector<size_t> buildJacob(size_t n);

		template <typename T>
		void insertNbr(T &container, int value, size_t high) {
			size_t low = 0;

			while (low < high) {
				size_t mid = (low + high) / 2;

				if (container[mid] < value)
					low = mid + 1;
				else
					high = mid;
			}
			container.insert(container.begin() + low, value);
		}

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
			for (size_t i = 0; i < pairs.size(); i++)
				big.push_back(pairs[i].second);

			T main_chain = fordJohnson(big);

			if (!pairs.empty()) {
				size_t pos = std::lower_bound(main_chain.begin(), main_chain.end(), pairs[0].second) - main_chain.begin();
				insertNbr(main_chain, pairs[0].first, pos);
			}

			std::vector<size_t> jac_seq = buildJacob(pairs.size());
			size_t inserted = 1;
			for (size_t i = 0; i < jac_seq.size(); i++) {
				size_t jacob = jac_seq[i];
				if (jacob > pairs.size())
					jacob = pairs.size();
				for (size_t j = jacob; j > inserted; j--) {
					size_t index = j - 1;
					int value = pairs[index].first;
					int big_brother = pairs[index].second;
					size_t pos = std::lower_bound(main_chain.begin(), main_chain.end(), big_brother) - main_chain.begin();
					insertNbr(main_chain, value, pos);
				}
				inserted = jacob;
			}

			for (size_t i = inserted; i < pairs.size(); i++) {
				size_t pos = std::lower_bound(main_chain.begin(), main_chain.end(), pairs[i].second) - main_chain.begin();
				insertNbr(main_chain, pairs[i].first, pos);
			}
			if (has_odd)
				insertNbr(main_chain, odd_value, main_chain.size());
			return main_chain;
		}
};
