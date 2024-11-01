/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:09:49 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 14:39:11 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	int	result;
	int	neg;
	int	i;

	neg = 1;
	result = 0;
	i = 0;
	if (nptr[0] == ' ')
		while (nptr[i] == ' ')
			i++;
	if ((nptr[i] == '-' || nptr[i] == '+')
		&& (nptr[i + 1] >= '0' && nptr[i + 1] <= '9'))
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * neg);
}
/*
int	main(void)
{
	char nbr[] = "   -+ 2147483648";

	printf("The number is: %i\n", ft_atoi(nbr));
	return (0);
}
*/
