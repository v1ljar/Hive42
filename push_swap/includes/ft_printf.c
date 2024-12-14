/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:50:12 by vuljas            #+#    #+#             */
/*   Updated: 2024/12/03 12:17:12 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_format(const char specifier, va_list ap);
static int	ft_validate_specif(const char specif, va_list ap);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		counter;
	int		res;

	counter = 0;
	res = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
			res = ft_validate_specif(*(++format), ap);
		else
			res = write(1, &(*format), 1);
		if (res == -1)
			return (-1);
		counter += res;
		format++;
	}
	va_end(ap);
	return (counter);
}

static int	ft_validate_specif(const char specif, va_list ap)
{
	char	*symbols;
	int		count;
	int		res;

	count = 0;
	res = 0;
	symbols = "cspdiuxX%";
	while (*symbols)
	{
		if (specif == *symbols)
		{
			count = 1;
			break ;
		}
		symbols++;
	}
	if (count == 1)
		res = ft_print_format(specif, ap);
	if (count == 0)
		res = ft_print_char(specif - 1);
	return (res);
}

static int	ft_print_format(const char specifier, va_list ap)
{
	int	cnt;
	int	res;

	cnt = 0;
	res = 0;
	if (specifier == 'c')
		res = ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		res = ft_print_str(va_arg(ap, char *));
	else if (specifier == 'i' || specifier == 'd')
		res = ft_print_digit(va_arg(ap, int), BASE10, 10);
	else if (specifier == 'u')
		res = ft_print_digit(va_arg(ap, unsigned int), BASE10, 10);
	else if (specifier == 'p')
		res = ft_print_pointer(va_arg(ap, void *), BASE10, 16);
	else if (specifier == 'x')
		res = ft_print_digit(va_arg(ap, unsigned int), BASE10, 16);
	else if (specifier == 'X')
		res = ft_print_digit(va_arg(ap, unsigned int), BASE16CAP, 16);
	else if (specifier == '%')
		res = ft_print_char('%');
	if (res == -1)
		return (-1);
	cnt += res;
	return (cnt);
}
