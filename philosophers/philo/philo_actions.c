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
		pthread_mutex_lock(info->right_fork);
		print_msg(info, "has taken right_fork");
	}
	else
	{
		pthread_mutex_lock(info->left_fork);
		print_msg(info, "has taken left_fork");
	}
	if (info->master->dead)
	{
		unlock_first_fork(info);
		return (-1);
	}
	return (0);
}

int	lock_second_fork(t_philo *info)
{
	if (info->master->dead)
	{
		unlock_first_fork(info);
		return (-1);
	}
	if (info->master->philos == 1)
		return (0);
	if (info->id % 2 != 0)
	{
		pthread_mutex_lock(info->left_fork);
		print_msg(info, "has taken left_fork");
	}
	else
	{
		pthread_mutex_lock(info->right_fork);
		print_msg(info, "has taken right_fork");
	}
	if (info->master->dead)
	{
		unlock_first_fork(info);
		unlock_second_fork(info);
		return (-1);
	}
	return (0);
}

int	unlock_first_fork(t_philo *info)
{
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
		return (unlock_second_fork(info));
	return (0);
}

int	unlock_second_fork(t_philo *info)
{
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

int	create_philo_thread(t_master *master, int *i, t_philo *phil_data)
{
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
	pthread_create(&master->arr_philos[*i]->phil, NULL, philo_routine,
		master->arr_philos[*i]);
	(*i)++;
	return (0);
}
