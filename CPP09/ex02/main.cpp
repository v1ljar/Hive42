#include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac == 1) {
        std::cerr << "Program requires a positive integer sequence as an argument!\n";
        return (1);
    }
    for (int i = 1; i < ac; i++) {
        std::cout << av[i] << " ";
    }
    std::cout << "\n";
    return (0);
}