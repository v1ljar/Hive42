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

static int	init_master(t_master *master, int ac, char **av);
static int	validate_args(int ac, char **av, int i, int j);
static int	init_values(int ac, char **av, t_master *master);
static int	init_n_join_forks_n_threads(t_master *master, int i);

int	main(int ac, char **av)
{
	static t_master	master;

	if (init_master(&master, ac, av) == -1)
		return (1);
	clean_up(&master);
	return (0);
}

static int	init_master(t_master *master, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Must have following arguments:\n\tnumber_of_philosophers\n\t"
				"time_to_die\n\ttime_to_eat\n\ttime_to_sleep\n\t"
				"[number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	if (validate_args(ac, av, 1, 0) == -1)
		return (-1);
	if (init_values(ac, av, master))
		return (-1);
	return (0);
}

static int	validate_args(int ac, char **av, int i, int j)
{
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][0] == '0' || !(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Invalid argument: `%s´\n%s\n", av[i],
						"Only positive integers allowed!");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_values(int ac, char **av, t_master *master)
{
	master->philos = p_atol(av[1]);
	master->time_to_die = p_atol(av[2]);
	master->eat_time = p_atol(av[3]);
	master->sleep_time = p_atol(av[4]);
	if (ac == 6)
		master->meals = p_atol(av[5]);
	else
		master->meals = -1;
	if (master->time_to_die < 60 || master->eat_time < 60
		|| master->sleep_time < 60)
		return (printf("Time values must be creater than 60\n"));
	master->dead = false;
	master->arr_philos = malloc(sizeof(t_philo *) * master->philos);
	if (!master->arr_philos)
		return (printf("Philos array allocation failed\n"));
	master->write_lock = malloc(sizeof(pthread_mutex_t));
	if (!master->write_lock)
		return (printf("Write lock mutex failed\n"));
	if (pthread_mutex_init(master->write_lock, NULL) != 0)
		return (printf("Mutex lock initialization failed\n"));
	master->forks = malloc(sizeof(pthread_mutex_t) * master->philos);
	if (!master->forks)
		return (printf("Forks allocation failed\n"));
	return (init_n_join_forks_n_threads(master, 0));
}

static int	init_n_join_forks_n_threads(t_master *master, int i)
{
	while (i < master->philos)
	{
		if (pthread_mutex_init(&master->forks[i], NULL) != 0)
		{
			clean_up(master);
			return (printf("Mutex init failed\n"));
		}
		i++;
	}
	if (pthread_create(&master->monitoring, NULL, monitoring_routine, master))
		return (free_n_print(master, "Monitoring thread creation failed"));
	i = 0;
	while (i < master->philos)
	{
		if (create_philo_thread(master, &i, NULL))
			return (-1);
	}
	i = 0;
	while (i < master->philos)
		if (pthread_join(master->arr_philos[i++]->phil, NULL) != 0)
			return (free_n_print(master, "Philosopher thread join failed"));
	if (pthread_join(master->monitoring, NULL) != 0)
		return (free_n_print(master, "Monitoring thread join failed"));
	return (0);
}
