/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:15:56 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/28 11:23:17 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	monitoring_start_routine(t_master *master);
static int	start_routine(void *data, t_philo **info);
static int	eat_routine(t_philo *info, long target_time);

void	*philo_routine(void *data)
{
	t_philo	*info;

	if (start_routine(data, &info) == -1)
		return (NULL);
	while (info->master->meals == -1 || info->courses != info->master->meals)
	{
		if (lock_first_fork(info) == -1 || lock_second_fork(info) == -1)
			return (NULL);
		if (eat_routine(info, 0) == -1)
			return (NULL);
		if (unlock_first_fork(info, 1) == -1 || unlock_second_fork(info) == -1)
			return (NULL);
		if (info->master->meals != -1)
		{
			if (increment_courses(info) == -1)
				return (NULL);
		}
		if (sleep_routine(info) == -1)
			return (NULL);
		print_msg(info, "is thinking");
		usleep(3000);
	}
	return (NULL);
}

void	*monitoring_routine(void *data)
{
	t_master	*ms;
	int			i;
	int			full;

	ms = (t_master *)data;
	if (monitoring_start_routine(ms) != 0)
		return (NULL);
	while (1)
	{
		full = 0;
		i = 0;
		while (i < ms->philos)
		{
			if (check_philo_death(ms, i, &full) == -1)
				return (NULL);
			i++;
		}
		if (ms->meals != -1 && full == ms->philos)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	monitoring_start_routine(t_master *master)
{
	long	target_time;

	while (!master->philos_ready)
	{
		pthread_mutex_lock(master->write_lock);
		if (master->start + 4 <= get_time(master, NULL))
			master->start = get_time(master, NULL) + 10;
		if (master->dead == true)
			return (-1);
		pthread_mutex_unlock(master->write_lock);
		usleep(500);
	}
	pthread_mutex_lock(master->write_lock);
	target_time = master->start;
	pthread_mutex_unlock(master->write_lock);
	while (get_time(master, NULL) < target_time)
	{
		if (master->dead == true)
			return (-1);
		usleep(500);
	}
	usleep(3000);
	return (0);
}

static int	start_routine(void *data, t_philo **info)
{
	long	target_time;

	if (wait_for_start(data, info) != 0)
		return (-1);
	pthread_mutex_lock(&(*info)->access_lock);
	(*info)->last_meal = get_time(NULL, *info);
	target_time = (*info)->last_meal + (*info)->master->eat_time;
	pthread_mutex_unlock(&(*info)->access_lock);
	if (((*info)->master->philos > 2 && (*info)->id % 2 != 0
			&& (*info)->id == (*info)->master->philos) || (*info)->id % 2 == 0)
	{
		print_msg(*info, "is thinking");
		while (get_time(NULL, *info) < target_time)
		{
			if ((*info)->master->dead == true)
				return (-1);
			usleep(1000);
		}
		if ((*info)->id % 2 != 0)
			usleep(1000);
	}
	return (0);
}

static int	eat_routine(t_philo *info, long target_time)
{
	if (info->master->philos != 1)
		print_msg(info, "is eating");
	pthread_mutex_lock(&info->access_lock);
	info->last_meal = get_time(NULL, info);
	target_time = info->last_meal + info->master->eat_time;
	pthread_mutex_unlock(&info->access_lock);
	if (info->master->philos == 1)
	{
		while (1)
		{
			if (info->master->dead == true)
				return (unlock_first_fork(info, 0), -1);
			usleep(1000);
		}
	}
	while (get_time(NULL, info) < target_time)
	{
		if (info->master->dead == true)
			return (unlock_first_fork(info, 1), -1);
		usleep(1000);
	}
	return (0);
}
