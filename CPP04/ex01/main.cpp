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

	std::cout << "\t[ More tests with array of Animal objects]" << std::endl;
	int	nbr = 4;
	int n;
	Animal*	animals[nbr];

	for (n = 0; n < nbr; n++)
	{
		if (n < nbr / 2)
			animals[n] = new Dog();
		else
			animals[n] = new Cat();
	}
	for (n = 0; n < nbr; n++)
		delete animals[n];
	// delete animals;
	return 0;
}