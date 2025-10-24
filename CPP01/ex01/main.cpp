#include "Zombie.hpp"

int	main()
{
	Zombie	*crew;
	int		N;

	N = 5;
	crew = zombieHorde(N, "Liina");
	for (int i = 0; i < N; i++)
	{
		crew[i].announce();
	}
	delete[] crew;
	return (0);
}
