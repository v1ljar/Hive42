/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:25 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/28 13:24:31 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_overflow(t_master *master)
{
	if (master->time_to_die > INT_MAX || master->eat_time > INT_MAX
		|| master->sleep_time > INT_MAX || (master->meals != -1
			&& master->meals > INT_MAX))
		return (printf("Values are overflowing INT_MAX,"
				"please enter reasonable values!\n"));
	return (0);
}

int	free_philos_arr(t_master *master, int *i, int mode)
{
	while (*i >= 0)
	{
		if (master->arr_philos[*i])
			free(master->arr_philos[*i]);
		(*i)--;
		if (mode == 1 && *i >= 0)
			pthread_mutex_destroy(&master->arr_philos[*i]->access_lock);
	}
	free(master->arr_philos);
	if (mode == 0)
		return (printf("Philo_data allocation failed\n"));
	else
		return (printf("Philo_data access_lock init failed\n"));
}
