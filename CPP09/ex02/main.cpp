// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/02/12 10:39:11 by vuljas            #+#    #+#             //
//   Updated: 2026/02/12 10:39:13 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PmergeMe.hpp"

int main(int ac, char **av) {
	if (ac == 1) {
		std::cerr << "Program requires a positive integer sequence as an argument!\n";
		return (1);
	}

	PmergeMe master;
	try {
		master.check_args_fill(ac, av);
		master.print_before();

		auto vec_start = std::chrono::high_resolution_clock::now();
		std::vector<int> vecSorted = master.fordJohnson(master.get_vec());
		auto vec_end = std::chrono::high_resolution_clock::now();

		auto deq_start = std::chrono::high_resolution_clock::now();
		std::deque<int> deqSorted = master.fordJohnson(master.get_deq());
		auto deq_end = std::chrono::high_resolution_clock::now();

		std::cout << "After : ";
		for (size_t i = 0; i < vecSorted.size(); i++) {
			std::cout << vecSorted[i];
			if (i + 1 != vecSorted.size())
				std::cout << " ";
		}
		std::cout << "\n";

		auto vec_time = std::chrono::duration_cast<std::chrono::microseconds>(vec_end - vec_start);
		std::cout << "Time to process " << master.get_vec().size()
				  << " elements with vector: " << (vec_time).count() << " us\n";

		auto deq_time = std::chrono::duration_cast<std::chrono::microseconds>(deq_end - deq_start);
		std::cout << "Time to process " << master.get_deq().size()
				  << " elements with deque: " << deq_time.count() << " us\n";
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return (2);
	}
	return (0);
}
