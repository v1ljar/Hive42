/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:15:56 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/13 11:16:00 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_routine(void *data, t_philo **info);
static int	eat_routine(t_philo *info);
static int	sleep_routine(t_philo *info);

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
		if (unlock_first_fork(info) == -1 || unlock_second_fork(info) == -1)
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

void	*monitoring_routine(void *data)
{
	t_master	*ms;
	int			i;
	int			full;

	ms = (t_master *)data;
	while (get_time() < ms->start)
		usleep(500);
	while (1)
	{
		full = 0;
		i = 0;
		while (i < ms->philos)
		{
			if (ms->meals != -1 && ms->arr_philos[i]->courses == ms->meals)
				full++;
			if ((ms->meals == -1 || ms->arr_philos[i]->courses < ms->meals)
				&& get_time() - ms->arr_philos[i]->last_meal > ms->time_to_die)
				return (print_died(ms, i));
			i++;
		}
		if (ms->meals != -1 && full == ms->philos)
			return (NULL);
	}
	return (NULL);
}

static int	start_routine(void *data, t_philo **info)
{
	*info = (t_philo *)data;
	while (get_time() < (*info)->master->start)
		usleep(500);
	if (((*info)->master->philos > 2 && (*info)->id % 2 != 0
			&& (*info)->id == (*info)->master->philos) || (*info)->id % 2 == 0)
	{
		print_msg(*info, "is thinking");
		while (get_time() < (*info)->last_meal + (*info)->master->eat_time)
		{
			if ((*info)->master->dead == true)
				return (-1);
			usleep(500);
		}
	}
	return (0);
}

static int	eat_routine(t_philo *info)
{
	print_msg(info, "is eating");
	info->last_meal = get_time();
	while (get_time() < info->last_meal + info->master->eat_time)
	{
		if (info->master->dead == true)
		{
			unlock_first_fork(info);
			unlock_second_fork(info);
			return (-1);
		}
		usleep(500);
	}
	return (0);
}

static int	sleep_routine(t_philo *info)
{
	print_msg(info, "is sleeping");
	while (get_time() < info->last_meal + info->master->sleep_time
		+ info->master->eat_time)
	{
		if (info->master->dead == true)
			return (-1);
		usleep(1000);
	}
	return (0);
}
