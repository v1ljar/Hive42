#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	std::cout << "\t[ Creating objects ]" << std::endl;
	const Animal* meta = new Animal();

	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n\t[ Testing getType() ]" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << meta->getType() << " " << std::endl;
	std::cout << "\n\t[ Testing makeSound() ]" << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	std::cout << "\n\t[ Destruction ]" << std::endl;
	delete meta;
	delete j;
	delete i;

	return 0;
}