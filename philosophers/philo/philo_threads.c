/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:44:25 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/29 13:24:31 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_n_join_threads(t_master *master, int j, int k, int value)
{
	if (pthread_create(&master->monitoring, NULL, monitoring_routine, master))
		return (printf("Monitoring thread creation failed!\n"));
	while (j < master->philos)
	{
		value = create_philo_thread(master, &j, NULL);
		if (value == -1)
		{
			master->dead = true;
			if (pthread_join(master->monitoring, NULL) != 0)
				printf("Monitoring join failed!\n");
			while (--j >= 0)
			{
				if (pthread_join(master->arr_philos[j]->phil, NULL) != 0)
					printf("Philo id %i thread join failed!\n", j + 1);
			}
			return (printf("Philo thread creation failed!\n"));
		}
		else if (value != 0)
			return (1);
	}
	master->philos_ready = true;
	return (join_threads(master, k));
}

int	create_philo_thread(t_master *master, int *i, t_philo *phil_data)
{
	phil_data = malloc(sizeof(t_philo));
	if (!phil_data)
		return (-1);
	memset(phil_data, '\0', sizeof(t_philo));
	if (pthread_mutex_init(&phil_data->access_lock, NULL))
		return (-1);
	phil_data->id = *i + 1;
	if (master->philos > 1)
		phil_data->left_fork = &master->forks[((*i) + 1) % master->philos];
	phil_data->right_fork = &master->forks[*i];
	pthread_mutex_lock(&phil_data->access_lock);
	phil_data->last_meal = master->start;
	phil_data->courses = 0;
	phil_data->master = master;
	master->arr_philos[*i] = phil_data;
	pthread_mutex_unlock(&phil_data->access_lock);
	if (pthread_create(&master->arr_philos[*i]->phil, NULL, philo_routine,
			master->arr_philos[*i]))
		return (-1);
	(*i)++;
	return (0);
}

int	join_threads(t_master *master, int k)
{
	if (pthread_join(master->monitoring, NULL) != 0)
	{
		master->dead = true;
		usleep(3000);
		return (printf("Monitoring join failed!\n"));
	}
	while (k < master->philos)
	{
		if (pthread_join(master->arr_philos[k++]->phil, NULL) != 0)
		{
			master->dead = true;
			usleep(3000);
			return (printf("Philos join failed!\n"));
		}
	}
	return (0);
}
