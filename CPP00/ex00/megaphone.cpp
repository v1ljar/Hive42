#include <iostream>

int	main(int ac, char **av)
{
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int i = 1; i < ac; i++)
		{
			for (int j = 0; av[i][j];j++)
			{
				if (av[i][j] >= 'a' && av[i][j] <= 'z')
					std::cout << static_cast<char>(av[i][j] - ('a' - 'A'));
				else if (av[i][j] == ' ' && j == 0)
					continue ;
				else
					std::cout << av[i][j];
			}
			if (i + 1 < ac)
				std::cout << " ";
		}
		std::cout << "\n";
	}
	return (0);
}