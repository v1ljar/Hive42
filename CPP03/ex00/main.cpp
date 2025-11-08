#include "ClapTrap.hpp"

int	main()
{
	int	i;

	std::cout << "\n\t *** [ TEST 1 Parametrized constructor, create mimi with name Mimi ] ***" << std::endl;
	ClapTrap mimi("Mimi");

	std::cout << "\n\t *** [ TEST 2 Copy constructor, create lala with mimi content ] ***" << std::endl;
	ClapTrap lala(mimi);

	std::cout << "\n\t *** [ TEST 3 Copy operator constructor, create rex and assign to mimi content ] ***" << std::endl;
	ClapTrap rex("Rex");
	rex = mimi;

	std::cout << "\n\t *** [ TEST 4 Member functions interactions, rex attack lala, lala takes damage(5) and repairs(2) ] ***" << std::endl;
	rex.attack("Lala");
	lala.takeDamage(5);
	lala.beRepaired(2);

	std::cout << "\n\t *** [ TEST 5 lala lost mind and attack 12 times ] ***" << std::endl;
	for (i = 1; i <= 12; i++)
	{
		lala.attack("Target" + std::to_string(i));
	}

	std::cout << "\n\t *** [ TEST 6 lala (with no energy points) tries to repair ] ***" << std::endl;
	lala.beRepaired(5);

	std::cout << "\n\t *** [ TEST 7 lala (with 7 hit points after TEST 4), was attacked 10 times ] ***" << std::endl;
	for (i = 1; i <= 10; i++)
	{
		lala.takeDamage(1);
	}

	std::cout << "\n\t *** [ TEST 8 lala (dead), tries to repair ] ***" << std::endl;
	lala.beRepaired(5);

	std::cout << "\n\t*** [ END OF TESTS - Destructors will now be called automatically ] ***" << std::endl;

	return (0);
}