#include "FragTrap.hpp"

int	main()
{
	int	i;

	std::cout << "\n\t *** [ TEST 1 Parametrized constructor, create mimi with name Mimi ] ***" << std::endl;
	FragTrap mimi("Mimi");

	std::cout << "\n\t *** [ TEST 2 Copy constructor, create lala with mimi content ] ***" << std::endl;
	FragTrap lala(mimi);

	std::cout << "\n\t *** [ TEST 3 Copy operator constructor, create rex and assign to mimi content ] ***" << std::endl;
	FragTrap rex("Rex");
	rex = mimi;

	std::cout << "\n\t *** [ TEST 4 Member functions interactions, rex attack lala, lala takes damage(30) and repairs(20) ] ***" << std::endl;
	rex.attack("Lala");
	lala.takeDamage(30);
	lala.beRepaired(20);

	std::cout << "\n\t *** [ TEST 5 lala lost mind and attack 100 times ] ***" << std::endl;
	for (i = 1; i <= 100; i++)
	{
		lala.attack("Target" + std::to_string(i));
	}

	std::cout << "\n\t *** [ TEST 6 lala (with no energy points) tries to repair ] ***" << std::endl;
	lala.beRepaired(20);

	std::cout << "\n\t *** [ TEST 7 lala (with 90 hit points after TEST 4), was attacked 5 times ] ***" << std::endl;
	for (i = 1; i <= 5; i++)
	{
		lala.takeDamage(30);
	}

	std::cout << "\n\t *** [ TEST 8 lala (dead), tries to repair ] ***" << std::endl;
	lala.beRepaired(5);

	std::cout << "\n\t *** [ TEST 9 highFivesGuys() ] ***" << std::endl;
	lala.highFivesGuys();
	mimi.highFivesGuys();
	rex.highFivesGuys();


	std::cout << "\n\t*** [ END OF TESTS - Destructors will now be called automatically ] ***" << std::endl;

	return (0);
}