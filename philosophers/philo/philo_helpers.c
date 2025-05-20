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

int	sleep_routine(t_philo *info)
{
	print_msg(info, "is sleeping");
	while (get_time(NULL, info) < info->last_meal + info->master->sleep_time
		+ info->master->eat_time)
	{
		if (info->master->dead == true)
			return (-1);
		usleep(500);
	}
	return (0);
}

int	create_monitor_n_join_threads(t_master *master, int k)
{
	if (pthread_create(&master->monitoring, NULL, monitoring_routine, master))
	{
		master->dead = true;
		clean_up(master);
		return (printf("Monitoring thread creation failed!\n"));
	}
	master->philos_ready = true;
	if (pthread_join(master->monitoring, NULL) != 0)
	{
		master->dead = true;
		usleep(3000);
		return (printf("Monitoring join failed!\n"));
	}
	while (k < master->philos)
	{
		if (pthread_join(master->arr_philos[k++]->phil, NULL) != 0)
		{
			master->dead = true;
			usleep(3000);
			return (printf("Philos join failed!\n"));
		}
	}
	return (0);
}

int	check_overflow(t_master *master)
{
	if (master->time_to_die > INT_MAX || master->eat_time > INT_MAX
		|| master->sleep_time > INT_MAX || master->meals > INT_MAX)
		return (printf("Values are overflowing INT_MAX,"
				"please enter reasonable values!\n"));
	return (0);
}
