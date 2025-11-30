#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Program requires only one parameter!\n";
		return (1);
	}
	try {
		ScalarConverter::convert(argv[1]);
	} catch (std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}