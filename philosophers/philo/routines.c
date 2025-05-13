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

void	*philo_routine(void *data)
{
	t_philo *info;

	info = (t_philo *)data;
	while(get_time() < info->master->start)
		usleep(100);
	if (info->id % 2 == 0)
		usleep(info->master->eat_time * 900);
	while (info->master->meals == -1 || info->courses < info->master->meals)
	{
		lock_fork(info);
		print_msg(info, "is eating");
		info->last_meal = get_time();
		while (get_time() < info->last_meal + info->master->eat_time)
		{
			if (info->master->dead == true)
				return (NULL);
			usleep(100);
		}
		unlock_fork(info);
		if (info->master->meals != -1)
		{
			info->courses++;
			if (info->courses == info->master->meals || info->master->dead == true)
				return (NULL);
		}
		print_msg(info, "is sleeping");
		while (get_time() < info->last_meal + info->master->sleep_time + info->master->eat_time)
		{
			if (info->master->dead == true)
				return (NULL);
			usleep(100);
		}
		print_msg(info, "is thinking");
	}
	return (NULL);
}

void	*monitoring_routine(void *data)
{
	t_master	*master;
	int			i;
	int			full;

	master = (t_master *)data;
	while(get_time() < master->start)
		usleep(100);
	while (1)
	{
		full = 0;
		i = 0;
		while (i < master->philos)
		{
			if (master->meals != -1 && master->arr_philos[i]->courses == master->meals)
				full++;
			if ((master->meals == -1 || master->arr_philos[i]->courses < master->meals)
					&& get_time() - master->arr_philos[i]->last_meal > master->time_to_die)
			{
				master->dead = true;
				printf("%li %i died\n", get_time() - master->start, i + 1);
				return (NULL);
			}
			i++;
		}
		if (master->meals != -1 && full == master->philos)
			return (NULL);
	}
	return (NULL);
}
