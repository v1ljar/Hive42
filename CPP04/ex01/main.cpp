#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "\t[ Given tests ]" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n\t[ Cleanup destructors ]" << std::endl;
	delete j;//should not create a leak
	delete i;

	std::cout << "\t[ More tests ]" << std::endl;
	return 0;
}