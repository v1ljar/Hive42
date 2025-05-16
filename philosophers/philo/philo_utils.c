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

long	get_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res = (long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (res);
}

void	clean_up(t_master *master)
{
	int	i;

	i = 0;
	while (master->forks && i < master->philos)
	{
		if (&master->forks[i])
			pthread_mutex_destroy(&master->forks[i]);
		i++;
	}
	if (master->forks)
		free(master->forks);
	i = 0;
	while (master->arr_philos && i < master->philos)
	{
		if (master->arr_philos[i])
			free(master->arr_philos[i]);
		i++;
	}
	if (master->arr_philos)
		free(master->arr_philos);
	if (master->write_lock)
		pthread_mutex_destroy(master->write_lock);
	if (master->write_lock)
		free(master->write_lock);
}

int	monitoring_start_routine(void *data, t_master **master)
{
	*master = (t_master *)data;
	while (!(*master)->ready_to_eat)
	{
		if ((*master)->dead == true)
			return (-1);
		usleep(500);
	}
	usleep(1000);
	return (0);
}
