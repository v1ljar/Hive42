/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:15:56 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/19 17:51:32 by vuljas           ###   ########.fr       */
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
	while (1)
	{
		if (lock_first_fork(info) == -1 || lock_second_fork(info) == -1)
			return (NULL);
		if (eat_routine(info, 0) == -1)
			return (NULL);
		if (unlock_first_fork(info, 1) == -1 || unlock_second_fork(info) == -1)
			return (NULL);
		if (info->master->meals != -1)
		{
			pthread_mutex_lock(&info->last_meal_lock);
			info->courses++;
			if (info->courses == info->master->meals || info->master->dead)
			{
				pthread_mutex_unlock(&info->last_meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&info->last_meal_lock);
		}
		if (sleep_routine(info) == -1)
			return (NULL);
		print_msg(info, "is thinking");
		usleep(1000);
	}
	return (NULL);
}

int	monitoring_start_routine(t_master *master)
{
	while (!master->philos_ready)
	{
		if (master->start + 4 <= get_time(master, NULL))
			master->start = get_time(master, NULL) + 10;
		if (master->dead == true)
			return (-1);
		usleep(500);
	}
	while (get_time(master, NULL) < master->start)
	{
		if (master->dead == true)
			return (-1);
		usleep(500);
	}
	usleep(500);
	return (0);
}

void	*monitoring_routine(void *data)
{
	t_master	*ms;
	int			i;
	int			full;
	long		target_time;

	ms = (t_master *)data;
	if (monitoring_start_routine(ms) != 0)
		return (NULL);
	while (1)
	{
		full = 0;
		i = 0;
		while (i < ms->philos)
		{
			pthread_mutex_lock(&ms->arr_philos[i]->last_meal_lock);
			if (ms->meals != -1 && ms->arr_philos[i]->courses == ms->meals)
				full++;
			target_time = get_time(ms, NULL) - ms->arr_philos[i]->last_meal;
			if ((ms->meals == -1 || ms->arr_philos[i]->courses < ms->meals)
				&& target_time >= ms->time_to_die)
			{
				pthread_mutex_unlock(&ms->arr_philos[i]->last_meal_lock);
				return (print_died(ms, i));
			}
			pthread_mutex_unlock(&ms->arr_philos[i]->last_meal_lock);
			i++;
		}
		if (ms->meals != -1 && full == ms->philos)
			return (NULL);
		usleep(333);
	}
	return (NULL);
}

static int	start_routine(void *data, t_philo **info)
{
	long	target_time;

	*info = (t_philo *)data;
	while (get_time(NULL, *info) < (*info)->master->start)
	{
		if ((*info)->master->dead == true)
			return (-1);
		pthread_mutex_lock(&(*info)->last_meal_lock);
		(*info)->last_meal = (*info)->master->start;
		pthread_mutex_unlock(&(*info)->last_meal_lock);
		usleep(500);
	}
	pthread_mutex_lock(&(*info)->last_meal_lock);
	(*info)->last_meal = get_time(NULL, *info);
	target_time = (*info)->last_meal + (*info)->master->eat_time;
	pthread_mutex_unlock(&(*info)->last_meal_lock);
	if (((*info)->master->philos > 2 && (*info)->id % 2 != 0
			&& (*info)->id == (*info)->master->philos) || (*info)->id % 2 == 0)
	{
		print_msg(*info, "is thinking");
		while (get_time(NULL, *info) < target_time)
		{
			if ((*info)->master->dead == true)
				return (-1);
			usleep(500);
		}
		if ((*info)->id % 2 != 0)
			usleep(250);
	}
	return (0);
}

static int	eat_routine(t_philo *info, long target_time)
{
	print_msg(info, "is eating");
	pthread_mutex_lock(&info->last_meal_lock);
	info->last_meal = get_time(NULL, info);
	target_time = info->last_meal + info->master->eat_time;
	pthread_mutex_unlock(&info->last_meal_lock);
	if (info->master->philos == 1)
	{
		while (1)
		{
			if (info->master->dead == true)
			{
				unlock_first_fork(info, 1);
				return (-1);
			}
			usleep(500);
		}
	}
	while (get_time(NULL, info) < target_time)
	{
		if (info->master->dead == true)
		{
			unlock_first_fork(info, 1);
			return (-1);
		}
		usleep(733);
	}
	return (0);
}
