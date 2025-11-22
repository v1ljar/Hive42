#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "\t\t*** [ FORM CONSTRUCTOR TESTS ] ***" << std::endl;
	try {
		Form f1("Great Form", 50, 20);
		std::cout << f1 << std::endl;

		Form f2 = f1;
		std::cout << "Copy: " << f2 << std::endl;

		Form f3("Minimal Form", 150, 150);
		std::cout << f3 << std::endl;

	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n\t\t*** [ FORM INVALID GRADE TESTS ] ***" << std::endl;
	try {
		Form bad1("TooHigh", 0, 10);
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	try {
		Form bad2("TooLow", 151, 10);
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n\t\t*** [ FORM SIGNING TESTS ] ***" << std::endl;
	try {
		Form f1("Contract", 50, 10);
		Bureaucrat john("John", 40);
		Bureaucrat mark("Mark", 140);

		std::cout << f1 << std::endl;
		std::cout << john << std::endl;
		std::cout << mark << std::endl;

		mark.signForm(f1);
		john.signForm(f1);

		std::cout << f1 << std::endl;

	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n\t\t*** [ DYNAMIC ALLOCATION + DESTRUCTOR TEST ] ***" << std::endl;
	try {
		Bureaucrat *p = new Bureaucrat("Dynamic Dan", 10);
		std::cout << *p << std::endl;

		Form *f = new Form("Dynamic Form", 20, 20);
		std::cout << *f << std::endl;

		p->signForm(*f);

		delete p;
		delete f;
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
return 0;
}
