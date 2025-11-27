#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

int main()
{
	std::cout << "\t\t*** [TESTS ] ***" << std::endl;
	try {
		Intern someRandomIntern;
		Bureaucrat bob("Bob", 1);
		AForm* rrf;
		try {
			rrf = someRandomIntern.makeForm("robotomy reqauest", "Bender");
		} catch (std::exception &e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		if (!rrf)
			return 1;
		rrf->beSigned(bob);
		bob.executeForm(*rrf);
		delete rrf;
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	return 0;
}
