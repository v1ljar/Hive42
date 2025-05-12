#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_master	t_master;

typedef struct s_philo
{
	pthread_t		phil;
	int				id;
	long			last_meal;
	long			courses;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_master		*master;
}	t_philo;

typedef struct s_master
{
	long			start;
	long			philos;
	long			think_time;
	long			eat_time;
	long			sleep_time;
	long			meals;
	t_philo			**arr_philos;
	pthread_mutex_t	*forks;
}	t_master;

long	p_atol(const char *str);
long	get_time(void);

#endif
