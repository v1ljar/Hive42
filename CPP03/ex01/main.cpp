#include "ScavTrap.hpp"

int	main()
{
	int	i;

	std::cout << "\n\t *** [ TEST 1 Parametrized constructor, create mimi with name Mimi ] ***" << std::endl;
	ScavTrap mimi("Mimi");

	std::cout << "\n\t *** [ TEST 2 Copy constructor, create lala with mimi content ] ***" << std::endl;
	ScavTrap lala(mimi);

	std::cout << "\n\t *** [ TEST 3 Copy operator constructor, create rex and assign to mimi content ] ***" << std::endl;
	ScavTrap rex("Rex");
	rex = mimi;

	std::cout << "\n\t *** [ TEST 4 Member functions interactions, rex attack lala, lala takes damage(20) and repairs(10) ] ***" << std::endl;
	rex.attack("Lala");
	lala.takeDamage(20);
	lala.beRepaired(10);

	std::cout << "\n\t *** [ TEST 5 lala lost mind and attack 50 times ] ***" << std::endl;
	for (i = 1; i <= 50; i++)
	{
		lala.attack("Target" + std::to_string(i));
	}

	std::cout << "\n\t *** [ TEST 6 lala (with no energy points) tries to repair ] ***" << std::endl;
	lala.beRepaired(5);

	std::cout << "\n\t *** [ TEST 7 lala (with 90 hit points after TEST 4), was attacked 10 times ] ***" << std::endl;
	for (i = 1; i <= 10; i++)
	{
		lala.takeDamage(20);
	}

	std::cout << "\n\t *** [ TEST 8 lala (dead), tries to repair ] ***" << std::endl;
	lala.beRepaired(5);

	std::cout << "\n\t *** [ TEST 9 GuardGate() ] ***" << std::endl;
	lala.guardGate();
	mimi.guardGate();
	rex.guardGate();


	std::cout << "\n\t*** [ END OF TESTS - Destructors will now be called automatically ] ***" << std::endl;

	return (0);
}