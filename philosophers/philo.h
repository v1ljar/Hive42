#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_master
{
	time_t	start;
	int		philos;
	int		think_time;
	int		eat_time;
	int		sleep_time;
	int		meals;
}	t_master;

int	p_atoi(const char *str);

#endif
