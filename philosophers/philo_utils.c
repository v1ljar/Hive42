#include "philo.h"

int	p_atoi(const char *str)
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
