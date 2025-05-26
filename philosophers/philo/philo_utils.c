/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:25 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/13 11:16:31 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	p_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

long	get_time(t_master *master, t_philo *phil)
{
	struct timeval	tv;
	unsigned long	res;

	if (gettimeofday(&tv, NULL) == -1)
	{
		if (master)
		{
			master->dead = true;
			usleep(1000);
			printf("gettimofday failed!\n");
		}
		else if (phil)
		{
			phil->master->dead = true;
			usleep(1000);
			printf("gettimofday failed!\n");
		}
		return (-1);
	}
	res = (unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((long)res);
}

void	print_msg(t_philo *info, char *str)
{
	pthread_mutex_lock(info->master->write_lock);
	if (!info->master->dead)
		printf("%li %i %s\n", get_time(NULL, info) - info->master->start,
			info->id, str);
	pthread_mutex_unlock(info->master->write_lock);
}

void	*print_died(t_master *master, int i)
{
	pthread_mutex_lock(master->write_lock);
	master->dead = true;
	printf("%li %i died\n", get_time(master, NULL) - master->start, i + 1);
	usleep(1000);
	pthread_mutex_unlock(master->write_lock);
	return (NULL);
}

void	clean_up(t_master *master)
{
	int	i;

	i = 0;
	while (master->forks && i < master->philos)
	{
		pthread_mutex_destroy(&master->forks[i++]);
	}
	if (master->forks)
		free(master->forks);
	i = 0;
	usleep(2000);
	while (master->arr_philos && i < master->philos)
	{
		if (master->arr_philos[i])
		{
			if (&master->arr_philos[i]->last_meal_lock)
				pthread_mutex_destroy(&master->arr_philos[i]->last_meal_lock);
			free(master->arr_philos[i]);
		}
		i++;
	}
	if (master->arr_philos)
		free(master->arr_philos);
	if (master->write_lock)
	{
		pthread_mutex_destroy(master->write_lock);
		free(master->write_lock);
	}
}
