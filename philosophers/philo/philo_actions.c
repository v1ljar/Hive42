/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:19:56 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/13 11:19:57 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_first_fork(t_philo *info)
{
	if (info->master->dead)
		return (-1);
	if (info->master->philos == 1)
	{
		if (pthread_mutex_lock(info->right_fork) == 0)
			print_msg(info, "has taken right_fork");
		return (0);
	}
	if (info->id % 2 != 0)
	{
		if (pthread_mutex_lock(info->right_fork) == 0)
			print_msg(info, "has taken right_fork");
	}
	else
	{
 		if (pthread_mutex_lock(info->left_fork) == 0)
			print_msg(info, "has taken left_fork");
	}
	if (info->master->dead)
		return (-1);
	return (0);
}

int	lock_second_fork(t_philo *info)
{
	if (info->master->dead)
		return (-1);
	if (info->master->philos == 1)
		return (0);
	if (info->id % 2 != 0)
	{
		if (pthread_mutex_lock(info->left_fork) == 0 && !info->master->dead)
			print_msg(info, "has taken left_fork");
	}
	else
	{
		if (pthread_mutex_lock(info->right_fork) == 0 && !info->master->dead)
			print_msg(info, "has taken right_fork");
	}
	if (info->master->dead)
		return (-1);
	return (0);
}

int	unlock_first_fork(t_philo *info)
{
	if (info->master->dead)
		return (-1);
	if (info->master->philos == 1)
	{
		pthread_mutex_unlock(info->right_fork);
		return (0);
	}
	if (info->id % 2 != 0)
		pthread_mutex_unlock(info->right_fork);
	else
		pthread_mutex_unlock(info->left_fork);
	if (info->master->dead)
		return (-1);
	return (0);
}

int	unlock_second_fork(t_philo *info)
{
	if (info->master->dead)
		return (-1);
	if (info->master->philos == 1)
		return (0);
	if (info->id % 2 != 0)
		pthread_mutex_unlock(info->left_fork);
	else
		pthread_mutex_unlock(info->right_fork);
	if (info->master->dead)
		return (-1);
	return (0);
}

void	print_msg(t_philo *info, char *str)
{
	long	time_atm;

	if (info->master->dead)
		return ;
	pthread_mutex_lock(info->master->write_lock);
	if (!info->master->dead)
	{
		time_atm = get_time();
		printf("%li %i %s\n", time_atm - info->master->start, info->id, str);
	}
	pthread_mutex_unlock(info->master->write_lock);
}

int	create_philo_thread(t_master *master, int *i)
{
	t_philo		*phil_data;

	phil_data = malloc(sizeof(t_philo));
	if (!phil_data)
	{
		while (*i >= 0)
		{
			if (master->arr_philos[*i])
				free(master->arr_philos[*i]);
			(*i)--;
		}
		free(master->arr_philos);
		return (printf("Philo_data allocation failed\n"));
	}
	phil_data->id = *i + 1;
	if (master->philos > 1)
		phil_data->left_fork = &master->forks[((*i) + 1) % master->philos];
	phil_data->right_fork = &master->forks[*i];
	phil_data->last_meal = master->start;
	phil_data->courses = 0;
	phil_data->master = master;
	master->arr_philos[*i] = phil_data;
	pthread_create(&master->arr_philos[*i]->phil, NULL, philo_routine, master->arr_philos[*i]);
	(*i)++;
	return (0);
}

void	clean_up(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->philos)
	{
		pthread_mutex_destroy(&master->forks[i++]);
	}
	free(master->forks);
	i = 0;
	usleep(2000);
	while (i < master->philos)
	{
		if (master->arr_philos[i])
			free(master->arr_philos[i]);
		i++;
	}
	free(master->arr_philos);
	pthread_mutex_destroy(master->write_lock);
	free(master->write_lock);
}
