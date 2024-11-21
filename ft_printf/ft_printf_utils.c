/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:13:10 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/21 17:04:47 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_print_str("(null)"));
	while (str[count] != '\0')
	{
		ft_print_char(str[count]);
		count++;
	}
	return (count);
}

int	ft_print_digit(long nbr, char *str, int base)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		count += (ft_print_digit(-nbr, str, base) + 1);
	}
	else if (nbr < base)
		count += write(1, &str[nbr], 1);
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

	nr = (unsigned long)ptr;
	if (nr == 0)
		return (ft_print_str("(nil)"));
	ft_print_str("0x");
	count = 2;
	if (nr < 0)
		ft_print_digit(-nr, str, base);
	else if (nr < (unsigned long)base)
		count += write(1, &str[nr], 1);
	else
	{
		count += ft_print_digit(nr / base, str, base);
		count += ft_print_digit(nr % base, str, base);
	}
	return (count);
}
