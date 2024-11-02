/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:09:49 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/02 10:51:51 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	result;
	int	neg;
	int	i;

	neg = 1;
	result = 0;
	i = 0;
<<<<<<< HEAD
	if (nptr[0] == ' ' || (nptr[0] >= 9 && nptr[0] <= 13))
		while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
=======
	if (nptr[0] == ' ' || (nptr[0] >= 3 && nptr[0] <= 13))
		while (nptr[i] == ' ' || (nptr[i] >= 3 && nptr[i] <= 13))
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
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
