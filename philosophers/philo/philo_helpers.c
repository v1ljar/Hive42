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

int	create_n_join_threads(t_master *master, int j, int k)
{
	if (pthread_create(&master->monitoring, NULL, monitoring_routine, master))
		return (printf("Monitoring thread creation failed!\n"));
	while (j < master->philos)
	{
		if (create_philo_thread(master, &j, NULL) == -1)
		{
			master->dead = true;
			if (pthread_join(master->monitoring, NULL) != 0)
				printf("Monitoring join failed!\n");
			while (--j >= 0)
				if (pthread_join(master->arr_philos[j]->phil, NULL) != 0)
					printf("Philo thread [index: %i] creation and join"
						"failed!\n", j);
			if (j == 0)
				return (printf("Philo thread creation failed!\n"));
		}
	}
	master->philos_ready = true;
	return (join_threads(master, k));
}

int	join_threads(t_master *master, int k)
{
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

int	sleep_routine(t_philo *info)
{
	long	target_time;

	print_msg(info, "is sleeping");
	pthread_mutex_lock(&info->last_meal_lock);
	target_time = info->last_meal + info->master->sleep_time
		+ info->master->eat_time;
	pthread_mutex_unlock(&info->last_meal_lock);
	while (get_time(NULL, info) < target_time)
	{
		if (info->master->dead == true)
			return (-1);
		usleep(500);
	}
	return (0);
}

int	check_overflow(t_master *master)
{
	if (master->time_to_die > INT_MAX || master->eat_time > INT_MAX
		|| master->sleep_time > INT_MAX || (master->meals != -1
		&& master->meals > INT_MAX))
		return (printf("Values are overflowing INT_MAX,"
				"please enter reasonable values!\n"));
	return (0);
}
