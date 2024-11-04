/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:15:56 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/04 14:15:50 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n);
static char	*ft_fill_str(char *res, int n, int count);

char	*ft_itoa(int n)
{
	char	*result;
	int		digits_count;

	if (n == '\0')
		return (NULL);
	digits_count = ft_count_digits(n);
	result = (char *)malloc(sizeof(char) * (digits_count + 1));
	if (!result)
		return (NULL);
	result = ft_fill_str(result, n, digits_count);
	return (result);
}

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	while (n)
	{
		count += 1;
		n = n / 10;
	}
	return (count);
}

static char	*ft_fill_str(char *res, int n, int count)
{
	int	len;
	int	neg;

	neg = 0;
	len = count;
	if (n < 0)
	{
		neg = 1;
		n *= -1;
	}
	while (count > 0)
	{
		res[count - 1] = n % 10 + '0';
		n = n / 10;
		count--;
	}
	if (neg)
		res[0] = '-';
	res[len] = '\0';
	return (res);
}
