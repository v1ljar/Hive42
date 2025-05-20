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
static int	eat_routine(t_philo *info);

void	*philo_routine(void *data)
{
	t_philo	*info;

	if (start_routine(data, &info) == -1)
		return (NULL);
	while (!info->master->dead && (info->master->meals == -1
			|| info->courses < info->master->meals))
	{
		if (lock_first_fork(info) == -1 || lock_second_fork(info) == -1)
			return (NULL);
		if (eat_routine(info) == -1)
			return (NULL);
		if (unlock_first_fork(info, 1) == -1 || unlock_second_fork(info) == -1)
			return (NULL);
		if (info->master->meals != -1)
		{
			info->courses++;
			if (info->courses == info->master->meals || info->master->dead)
				return (NULL);
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
		if (master->start + 2 <= get_time(master, NULL))
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

	ms = (t_master *)data;
	if (monitoring_start_routine(ms) != 0)
		return (NULL);
	while (1)
	{
		full = 0;
		i = 0;
		while (i < ms->philos)
		{
			if (ms->meals != -1 && ms->arr_philos[i]->courses == ms->meals)
				full++;
			if ((ms->meals == -1 || ms->arr_philos[i]->courses < ms->meals)
				&& get_time(ms, NULL) - ms->arr_philos[i]->last_meal
				>= ms->time_to_die)
				return (print_died(ms, i));
			i++;
		}
		if ((ms->meals != -1 && full == ms->philos) || ms->dead)
			return (NULL);
	}
	return (NULL);
}

static int	start_routine(void *data, t_philo **info)
{
	*info = (t_philo *)data;
	while (get_time(NULL, *info) < (*info)->master->start)
	{
		if ((*info)->master->dead == true)
			return (-1);
		(*info)->last_meal = (*info)->master->start;
		usleep(500);
	}
	(*info)->last_meal = get_time(NULL, *info);
	if (((*info)->master->philos > 2 && (*info)->id % 2 != 0
			&& (*info)->id == (*info)->master->philos) || (*info)->id % 2 == 0)
	{
		print_msg(*info, "is thinking");
		while (get_time(NULL, *info) < (*info)->last_meal
			+ (*info)->master->eat_time)
		{
			if ((*info)->master->dead == true)
				return (-1);
			usleep(250);
		}
		if ((*info)->id % 2 != 0)
			usleep(250);
	}
	return (0);
}

static int	eat_routine(t_philo *info)
{
	print_msg(info, "is eating");
	info->last_meal = get_time(NULL, info);
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
	while (get_time(NULL, info) < info->last_meal + info->master->eat_time)
	{
		if (info->master->dead == true)
		{
			unlock_first_fork(info, 1);
			return (-1);
		}
		usleep(500);
	}
	return (0);
}
