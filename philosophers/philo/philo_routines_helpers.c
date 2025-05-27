/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:15:56 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/19 17:51:32 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data_n_wait_start(void *data, t_philo **info)
{
	long	start;

	*info = (t_philo *)data;
	pthread_mutex_lock((*info)->master->write_lock);
	start = (*info)->master->start;
	pthread_mutex_unlock((*info)->master->write_lock);
	while (get_time(NULL, *info) < start)
	{
		if ((*info)->master->dead == true)
			return (-1);
		usleep(500);
		pthread_mutex_lock((*info)->master->write_lock);
		if (start < (*info)->master->start)
			start = (*info)->master->start;
		pthread_mutex_unlock((*info)->master->write_lock);
	}
	return (0);
}

int	increment_courses(t_philo *info)
{
	pthread_mutex_lock(&info->access_lock);
	info->courses++;
	if (info->courses == info->master->meals || info->master->dead)
	{
		pthread_mutex_unlock(&info->access_lock);
		return (-1);
	}
	pthread_mutex_unlock(&info->access_lock);
	return (0);
}

int	sleep_routine(t_philo *info)
{
	long	target_time;

	print_msg(info, "is sleeping");
	pthread_mutex_lock(&info->access_lock);
	target_time = info->last_meal + info->master->sleep_time
		+ info->master->eat_time;
	pthread_mutex_unlock(&info->access_lock);
	while (get_time(NULL, info) < target_time)
	{
		if (info->master->dead == true)
			return (-1);
		usleep(500);
	}
	return (0);
}

int	check_philo_death(t_master *master, int i, int *full)
{
	long		target_time;

	pthread_mutex_lock(&master->arr_philos[i]->access_lock);
	if (master->meals != -1 && master->arr_philos[i]->courses == master->meals)
		(*full)++;
	target_time = get_time(master, NULL) - master->arr_philos[i]->last_meal;
	if ((master->meals == -1 || master->arr_philos[i]->courses < master->meals)
		&& target_time >= master->time_to_die)
	{
		pthread_mutex_unlock(&master->arr_philos[i]->access_lock);
		print_died(master, i);
		usleep(1000);
		return (-1);
	}
	pthread_mutex_unlock(&master->arr_philos[i]->access_lock);
	return (0);
}
