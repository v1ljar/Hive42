#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	std::cout << "\t[ Creating objects ]" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n\t[ Testing getType() ]" << std::endl;
	std::cout << "Dog: " << j->getType() << " " << std::endl;
	std::cout << "Cat: " << i->getType() << " " << std::endl;
	std::cout << "Animal: " << meta->getType() << " " << std::endl;

	std::cout << "\n\t[ Testing makeSound() ]" << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << "\n\t[ Cleanup destructors ]" << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "\n\t[ Testing WrongAnimal WrongCat ]" << std::endl;
	const WrongAnimal* wrong = new WrongCat();

	std::cout << "WrongCat: " << wrong->getType() << " " << std::endl;
	wrong->makeSound();
	WrongCat	wrongcat;
	std::cout << wrongcat.getType() << " " << std::endl;
	wrongcat.makeSound();

	std::cout << "\n\t[ Destruction ]" << std::endl;
	delete wrong;
	return 0;
}