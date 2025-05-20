/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:16:10 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/13 11:16:14 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_master	t_master;

typedef struct s_philo
{
	pthread_t		phil;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_master		*master;
	_Atomic(long)	last_meal;
	_Atomic(long)	courses;
	int				id;
}	t_philo;

typedef struct s_master
{
	t_philo			**arr_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_lock;
	pthread_t		monitoring;
	_Atomic(bool)	dead;
	_Atomic(bool)	philos_ready;
	_Atomic(long)	start;
	long			philos;
	long			time_to_die;
	long			eat_time;
	long			sleep_time;
	long			meals;
}	t_master;

/*
 * Philo utils
*/
long	p_atol(const char *str);
long	get_time(t_master *master, t_philo *phil);
void	print_msg(t_philo *info, char *str);
void	*print_died(t_master *master, int i);
void	clean_up(t_master *master);
/*
 * Routines
*/
void	*philo_routine(void *data);
void	*monitoring_routine(void *data);
/*
 * Philo actions
*/
int		create_philo_thread(t_master *master, int *i, t_philo *phil_data);
int		lock_first_fork(t_philo *info);
int		lock_second_fork(t_philo *info);
int		unlock_first_fork(t_philo *info, int unlock);
int		unlock_second_fork(t_philo *info);
/*
 * Helpers
*/
int		sleep_routine(t_philo *info);
int		create_monitor_n_join_threads(t_master *master, int k);
int		check_overflow(t_master *master);

#endif
