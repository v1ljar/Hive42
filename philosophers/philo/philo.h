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
// Philo struct holds individual philo data and has access to master struct.
typedef struct s_philo
{
	pthread_t		phil;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	access_lock;
	t_master		*master;
	_Atomic long	last_meal;
	_Atomic long	courses;
	_Atomic int		id;
}	t_philo;
// Master struct hold all the data of the program.
typedef struct s_master
{
	t_philo			**arr_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_lock;
	pthread_t		monitoring;
	_Atomic bool	dead;
	_Atomic bool	philos_ready;
	_Atomic long	start;
	_Atomic long	philos;
	_Atomic long	time_to_die;
	_Atomic long	eat_time;
	_Atomic long	sleep_time;
	_Atomic long	meals;
}	t_master;

/*
 * Philo actions
*/
// Handles locking first lock respectively.
int		lock_first_fork(t_philo *info);
// Handles locking second lock respectively.
int		lock_second_fork(t_philo *info);
// Handles unlocking first lock respectively.
int		unlock_first_fork(t_philo *info, int unlock);
// Handles unlocking second lock respectively.
int		unlock_second_fork(t_philo *info);
/*
 * Philo helpers
*/
// Checks if given parameters are not greater than INT_MAX.
int		check_overflow(t_master *master);
// If create_philo_thread function fails, then it handles freeing accordingly.
int		free_philos_arr(t_master *master, int *i, int mode);
/*
 * Routines helpers
*/
// Start_routine helper, smart wait function for philos to start routine.
int		wait_for_start(void *data, t_philo **info);
// If meals amount specfied, function handles incrementing courses amount.
int		increment_courses(t_philo *info);
// Smart sleep function for philos.
int		sleep_routine(t_philo *info);
// Monitoring_routine helper, checks death of  philo
int		check_philo_death(t_master *master, int i, int *full);
/*
 * Routines
*/
// Philosopher thread routine
void	*philo_routine(void *data);
// Monitoring thread routine
void	*monitoring_routine(void *data);
/*
 * Philo threads
*/
// Handles threads creation process.
int		create_n_join_threads(t_master *master, int j, int k, int value);
// Handles initializing single philo data and its thread creation.
int		create_philo_thread(t_master *master, int *i, t_philo *phil_data);
// Handles (waiting) threads to be joined after the routines.
int		join_threads(t_master *master, int k);
/*
 * Philo utils
*/
// Ascii to long conversion.
long	p_atol(const char *str);
// Outputs time at the moment in ms.
long	get_time(t_master *master, t_philo *phil);
// Handles printing message accordingly
void	print_msg(t_philo *info, char *str);
// Check_philo_death helper, sets dead variable true and prints philos death.
void	*print_died(t_master *master, int i);
// Handles cleaning up master struct
void	clean_up(t_master *master, int i);

#endif
