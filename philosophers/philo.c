#include "philo.h"

int	init_master(t_master *master, int ac, char **av);
int	validate_args(int ac, char **av, int i, int j);

int	main(int ac, char **av)
{
	static t_master master;

	if (init_master(&master, ac, av) == -1)
		return (1);
	return (0);
}

int	init_master(t_master *master, int ac, char **av)
{
	struct timeval	tv;

	if (ac != 5 && ac != 6)
	{
		printf("Four (max five) arguments are required!\n");
		return (-1);
	}
	if (validate_args(ac, av, 1, 0) == -1)
		return (-1);
	gettimeofday(&tv, NULL);
	master->start = tv.tv_sec;
	master->philos = p_atoi(av[1]);
	master->think_time = p_atoi(av[2]);
	master->eat_time = p_atoi(av[3]);
	master->sleep_time = p_atoi(av[4]);
	if (ac == 6)
		master->meals = p_atoi(av[5]);
	return (0);
}

int	validate_args(int ac, char **av, int i, int j)
{
	while (i < ac)
	{
		while (av[i][j] != '\0')
		{
			if (av[i][0] == '0' || !(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Only positive integers allowed as arguments!\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
