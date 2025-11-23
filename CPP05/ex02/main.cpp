#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::cout << "\t\t*** [ AForm CONSTRUCTOR TESTS ] ***" << std::endl;
	std::cout << "\t\t\t[ Basic bureaucrat ]" << std::endl;
	try {
		Bureaucrat bur1("Basic", 150);
		ShrubberyCreationForm shrubhome("shrubhome");
		try {
			bur1.signAForm(shrubhome);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << shrubhome << "\n";
		try {
			shrubhome.execute(bur1);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}

		RobotomyRequestForm robohome("robohome");
		try {
			bur1.signAForm(robohome);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << robohome << "\n";
		bur1.executeForm(robohome);

		PresidentialPardonForm presipardon("Mr. Bean");
		try {
			bur1.signAForm(presipardon);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		try {
			presipardon.execute(bur1);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n\t\t\t[ Good bureaucrat ]" << std::endl;
	try {
		Bureaucrat bur2("Good", 15);
		ShrubberyCreationForm shrubhomeb2("shrubhomeb2");
		try {
			bur2.signAForm(shrubhomeb2);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << shrubhomeb2 << "\n";
		try {
			shrubhomeb2.execute(bur2);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}

		RobotomyRequestForm robohomeb2("robohomeb2");
		try {
			bur2.signAForm(robohomeb2);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << robohomeb2 << "\n";
		try {
			robohomeb2.execute(bur2);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}

		PresidentialPardonForm presipardon2("Mr. Bond");
		try {
			bur2.signAForm(presipardon2);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		try {
			presipardon2.execute(bur2);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}

	std::cout << "\n\t\t\t[ Greatest bureaucrat ]" << std::endl;
	try {
		Bureaucrat bur3("Greatest", 1);
		ShrubberyCreationForm shrubhomeb3("shrubhomeb3");
		try {
			bur3.signAForm(shrubhomeb3);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << shrubhomeb3 << "\n";
		try {
			shrubhomeb3.execute(bur3);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}

		RobotomyRequestForm robohomeb3("robohomeb3");
		try {
			bur3.signAForm(robohomeb3);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		std::cout << robohomeb3 << "\n";
		try {
			robohomeb3.execute(bur3);
		} catch(const std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}

		PresidentialPardonForm presipardon3("Mr. Trevor Philips");
		try {
			presipardon3.execute(bur3);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		try {
			bur3.signAForm(presipardon3);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
		try {
			presipardon3.execute(bur3);
		} catch (std::exception& e) {
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
	} catch (std::exception &e) {
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	return 0;
}
