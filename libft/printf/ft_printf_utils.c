/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:13:10 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/30 11:40:05 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	int	res;

	res = write(1, &c, 1);
	if (res == -1)
		return (-1);
	return (res);
}

int	ft_print_str(char *str)
{
	int	count;
	int	res;

	count = 0;
	if (str == NULL)
		return (ft_print_str("(null)"));
	while (str[count] != '\0')
	{
		res = ft_print_char(str[count]);
		if (res == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_print_digit(long nbr, char *str, int base)
{
	int	count;
	int	res;

	count = 0;
	if (nbr < 0)
	{
		res = write(1, "-", 1);
		if (res == -1)
			return (-1);
		count += res;
		nbr = -nbr;
	}
	if (nbr < base)
	{
		res = write(1, &str[nbr], 1);
		if (res == -1)
			return (-1);
		count += res;
	}
	else
	{
		count += ft_print_digit(nbr / base, str, base);
		count += ft_print_digit(nbr % base, str, base);
	}
	return (count);
}

int	ft_print_pointer(void *ptr, char *str, int base)
{
	unsigned long	nr;
	int				count;
	int				res;

	nr = (unsigned long)ptr;
	if (nr == 0)
		return (ft_print_str("(nil)"));
	ft_print_str("0x");
	count = 2;
	if (nr < (unsigned long)base)
	{
		res = write(1, &str[nr], 1);
		if (res == -1)
			return (-1);
		count += res;
	}
	else
	{
		count += ft_print_digit(nr / base, str, base);
		count += ft_print_digit(nr % base, str, base);
	}
	return (count);
}
