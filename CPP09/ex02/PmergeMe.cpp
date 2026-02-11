#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

// ---------------------------------------------------- Getters
const std::vector<int>& PmergeMe::get_vec() const {
	return (_vec);
}

const std::deque<int>& PmergeMe::get_deq() const {
	return (_deq);
}

// ---------------------------------------------------- Helper functions
void PmergeMe::check_args_fill(int ac, char **av) {
	for (int i = 1; i < ac; i++) {
		std::string str(av[i]);

		if (str.empty())
			throw std::runtime_error("Empty argument!");
		for (size_t j = 0; j < str.size(); j++) {
			if (str[j] >= '0' && str[j] <= '9')
				continue;
			else
				throw std::runtime_error("Invalid argument: [" + str + "]");
		}

		long nbr;
		nbr = std::atol(str.c_str());
		if (nbr < 0 || nbr > INT_MAX)
			throw std::runtime_error("Out of range: [" + str + "]");
		_vec.push_back(nbr);
		_deq.push_back(nbr);
	}
}

void PmergeMe::print_before() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i];
		if (i + 1 != _vec.size())
			std::cout << " ";
	}
	std::cout << "\n";
}

std::vector<size_t> PmergeMe::buildJacob(size_t n) {
	std::vector<size_t> result;

	if (n <= 1)
		return result;
	size_t i = 1;
	size_t j = 3;
	result.push_back(i);
	while (j < n) {
		result.push_back(j);
		size_t next = j + 2 * i;
		i = j;
		j = next;
	}
	return result;
}
