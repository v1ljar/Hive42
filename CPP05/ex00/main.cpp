#include "Bureaucrat.hpp"

int	main()
{
	std::cout << "\t\t*** [ Bureaucrat test with highest rank ] ***" << std::endl;
	try {
		Bureaucrat*	bur1;
		bur1 = new Bureaucrat("Viljar", 1);
		std::cout << "getName(): " << bur1->getName() << std::endl;
		std::cout << "getGrade(): " << bur1->getGrade() << std::endl;
		try {
			bur1->increment_grade();
			std::cout << "Incremented grade: " << bur1->getGrade() << std::endl;
		} catch (const Bureaucrat:: GradeTooHighException& e){
			std::cerr << "Increment Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Increment Exception caught: default exception!" << std::endl;
		}
		try {
			bur1->decrement_grade();
			std::cout << "Decremented grade: " << bur1->getGrade() << std::endl;
		} catch (const Bureaucrat::GradeTooLowException& e) {
			std::cerr << "Decrement Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Decrement Exception caught: default exception!" << std::endl;
		}
		std::cout << *bur1 << std::endl;
		delete bur1;
	} catch (const Bureaucrat::GradeTooHighException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (const Bureaucrat::GradeTooLowException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Exception caught: default exception!" << std::endl;
	}

	std::cout << "\n\t\t*** [ Bureaucrat test with lowest rank ] ***" << std::endl;
	try {
		Bureaucrat*	bur2;
		bur2 = new Bureaucrat();
		std::cout << "getName(): " << bur2->getName() << std::endl;
		std::cout << "getGrade(): " << bur2->getGrade() << std::endl;
		try {
			bur2->decrement_grade();
			std::cout << "Decremented grade: " << bur2->getGrade() << std::endl;
		} catch (const Bureaucrat::GradeTooLowException& e) {
			std::cerr << "Decrement Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Decrement Exception caught: default exception!" << std::endl;
		}
		try {
			bur2->increment_grade();
			std::cout << "Incremented grade: " << bur2->getGrade() << std::endl;
		} catch (const Bureaucrat:: GradeTooHighException& e){
			std::cerr << "Increment Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Increment Exception caught: default exception!" << std::endl;
		}
		std::cout << *bur2 << std::endl;
		delete bur2;
	} catch (const Bureaucrat::GradeTooHighException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (const Bureaucrat::GradeTooLowException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Exception caught: default exception!" << std::endl;
	}

	std::cout << "\n\t\t*** [ Bureaucrat test with invalid grade (151) ] ***" << std::endl;
	try {
		Bureaucrat*	bur3;
		bur3 = new Bureaucrat("Viljar", 151);
		std::cout << "getName(): " << bur3->getName() << std::endl;
		std::cout << "getGrade(): " << bur3->getGrade() << std::endl;
		try {
			bur3->increment_grade();
			std::cout << "Incremented grade: " << bur3->getGrade() << std::endl;
		} catch (const Bureaucrat:: GradeTooHighException& e){
			std::cerr << "Increment Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Increment Exception caught: default exception!" << std::endl;
		}
		try {
			bur3->decrement_grade();
			std::cout << "Decremented grade: " << bur3->getGrade() << std::endl;
		} catch (const Bureaucrat::GradeTooLowException& e) {
			std::cerr << "Decrement Exception caught: " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Decrement Exception caught: default exception!" << std::endl;
		}
		std::cout << *bur3 << std::endl;
		delete bur3;
	} catch (const Bureaucrat::GradeTooHighException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (const Bureaucrat::GradeTooLowException& e){
		std::cerr << "Exception caught: " << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Exception caught: default exception!" << std::endl;
	}

	std::cout << "\n\t\t*** [ Constructors test ] ***" << std::endl;
	Bureaucrat	bur1 = Bureaucrat();
	Bureaucrat	bur2(bur1);
	Bureaucrat	bur3("Mati", 1);
	bur3 = bur1;
	std::cout << "getName(): " << bur3.getName() << std::endl;
	std::cout << "getGrade(): " << bur3.getGrade() << std::endl;
	std::cout << "\t\t[ Destructors ]" << std::endl;
	return (0);
}