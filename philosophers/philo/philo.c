/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:15:39 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/13 11:15:44 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_master(t_master *master, int ac, char **av);
int		validate_args(int ac, char **av, int i, int j);
int		init_values(int ac, char **av, t_master *master, int i);

int	main(int ac, char **av)
{
	static t_master	master;

	if (init_master(&master, ac, av) == -1)
	{
		clean_up(&master);
		return (1);
	}
	clean_up(&master);
	return (0);
}

int	init_master(t_master *master, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Four (max five) arguments are required!\n");
		return (-1);
	}
	if (validate_args(ac, av, 1, 0) == -1)
		return (-1);
	if (init_values(ac, av, master, 0))
		return (-1);
	//printf("Todays crew:\n\tStart time: %li\n\tPhilos: %li\n\tTime_to die: %li\n\tTime_to eat: %li\n\tTime_to sleep: %li\n\tMeals amount: %li\n", master->start, master->philos, master->time_to_die, master->eat_time, master->sleep_time, master->meals);
	return (0);
}

int	validate_args(int ac, char **av, int i, int j)
{
	while (i < ac)
	{
		j = 0;
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

int	init_values(int ac, char **av, t_master *master, int i)
{
	master->philos = p_atol(av[1]);
	master->start = get_time() + (65 * master->philos);
	master->time_to_die = p_atol(av[2]);
	master->eat_time = p_atol(av[3]);
	master->sleep_time = p_atol(av[4]);
	if (ac == 6)
		master->meals = p_atol(av[5]);
	else
		master->meals = -1;
	if (master->time_to_die < 60 || master->eat_time < 60 || master->sleep_time < 60)
		return (printf("Time values must be creater than 60\n"));
	master->dead = false;
	master->arr_philos = malloc(sizeof(t_philo*) * master->philos);
	if (!master->arr_philos)
		return (printf("Philos array allocation failed\n"));
	memset(master->arr_philos, '\0', sizeof(t_philo*) * master->philos);
	master->write_lock = malloc(sizeof(pthread_mutex_t));
	if (!master->write_lock)
		return (printf("Write lock mutex failed\n"));
	if (pthread_mutex_init(master->write_lock, NULL) != 0)
		return (printf("Mutex lock initialization failed\n"));
	master->forks = malloc(sizeof(pthread_mutex_t) * master->philos);
	if (!master->forks)
		return (printf("Forks allocation failed\n"));
	while (i < master->philos)
	{
		if (pthread_mutex_init(&master->forks[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&master->forks[i]);
			}
			free(master->forks);
			free(master->write_lock);
			return (printf("Mutex init failed\n"));
		}
		i++;
	}
	i = 0;
	while (i < master->philos)
	{
		if (create_philo_thread(master, &i))
			return (-1);
	}
	pthread_create(&master->monitoring, NULL, monitoring_routine, master);
	i = 0;
	while (i < master->philos)
		pthread_join(master->arr_philos[i++]->phil, NULL);
	pthread_join(master->monitoring, NULL);
	return (0);
}
