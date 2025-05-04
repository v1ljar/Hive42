/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:59:12 by jpiensal          #+#    #+#             */
/*   Updated: 2024/11/14 12:38:41 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	long	nbr;

	nbr = n;
	count = count_len(nbr);
	str = malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		*str = '-';
	}
	str[count] = '\0';
	if (nbr == 0)
		str[--count] = '0';
	while (nbr > 0)
	{
		str[--count] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
