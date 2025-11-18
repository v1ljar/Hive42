#include "Bureaucrat.hpp"

int	main()
{
	Bureaucrat*	bur1;
	try {
		bur1 = new Bureaucrat("Jim", 5);
	} catch (const Bureaucrat::GradeTooHighException& e){
		std::cerr << "Exception caught: " << e.what();
	}
	std::cout << bur1->getName() << std::endl;
	std::cout << bur1->getGrade() << std::endl;
	bur1->increment_grade();
	std::cout << "Incremented grade: " << bur1->getGrade() << std::endl;
	bur1->decrement_grade();
	std::cout << "Decremented grade: " << bur1->getGrade() << std::endl;
	std::cout << *bur1;
	delete bur1;
	return (0);
}