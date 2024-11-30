/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:50:12 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/30 14:57:30 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_format(const char specifier, va_list ap);
static int	ft_validate_specif(const char specif);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		is_specif;
	int		res;

	count = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			is_specif = ft_validate_specif(*(++format));
			if (is_specif == 1)
			{
				res = ft_print_format(*format, ap);
				if (res == -1)
					return (-1);
			}
			if (is_specif == 0)
				count += ft_print_char(*(--format));
		}
		else
		{
			write(1, &(*format), 1);
			count++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}

static int	ft_validate_specif(const char specif)
{
	char	*symbols;

	symbols = "cspdiuxX%";
	while (*symbols)
	{
		if (specif == *symbols)
			return (1);
		symbols++;
	}
	return (0);
}

static int	ft_print_format(const char specifier, va_list ap)
{
	int	count;
	int	res;

	count = 0;
	if (specifier == 'c')
	{
		res = ft_print_char(va_arg(ap, int));
		if (res != 1)
			return (-1);
		count += res;
	}
	else if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'i' || specifier == 'd')
		count += ft_print_digit(va_arg(ap, int), BASE10, 10);
	else if (specifier == 'u')
		count += ft_print_digit(va_arg(ap, unsigned int), BASE10, 10);
	else if (specifier == 'p')
		count += ft_print_pointer(va_arg(ap, void *), BASE10, 16);
	else if (specifier == 'x')
		count += ft_print_digit(va_arg(ap, unsigned int), BASE10, 16);
	else if (specifier == 'X')
		count += ft_print_digit(va_arg(ap, unsigned int), BASE16CAP, 16);
	else if (specifier == '%')
		count += ft_print_char('%');
	return (count);
}
