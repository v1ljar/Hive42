#include "Harl.hpp"

int main()
{
	Harl	harl;

	std::cout << "[ Debug ]\n" << std::endl;
	harl.complain("DEBUG");
	std::cout << std::endl;
	std::cout << "[Info ]\n" << std::endl;
	harl.complain("INFO");
	std::cout << std::endl;
	std::cout << "[ Warning ]\n" << std::endl;
	harl.complain("WARNING");
	std::cout << std::endl;
	std::cout << "[ Error ]\n" << std::endl;
	harl.complain("ERROR");
	std::cout << std::endl;
	return 0;
}
