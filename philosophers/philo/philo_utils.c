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

void	print_msg(t_philo *info, char *str)
{
	long	time_atm;

	pthread_mutex_lock(info->master->write_lock);
	if (!info->master->dead)
	{
		time_atm = get_time();
		printf("%li %i %s\n", time_atm - info->master->start, info->id, str);
	}
	pthread_mutex_unlock(info->master->write_lock);
}

void	*print_died(t_master *master, int i)
{
	pthread_mutex_lock(master->write_lock);
	master->dead = true;
	printf("%li %i died\n", get_time() - master->start, i + 1);
	pthread_mutex_unlock(master->write_lock);
	return (NULL);
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
