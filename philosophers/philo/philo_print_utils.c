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

int	free_n_print(t_master *master, char *str)
{
	master->dead = true;
	usleep(1000);
	clean_up(master);
	printf("%s\n", str);
	return (1);
}
