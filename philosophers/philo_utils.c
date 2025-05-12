#include "philo.h"

long	p_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
			result = (result * 10) + (str[i] - '0');
			i++;
	}
	return (result);
}

long	get_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 0;
	res = (long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (res);
}
