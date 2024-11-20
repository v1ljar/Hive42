/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:50:12 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/20 14:08:49 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define	BASE10 "0123456789abcdef"
#define	BASE16CAP "0123456789ABCDEF"

int	ft_print_format(const char specifier, va_list ap);
int	ft_print_char(int c);
int	ft_print_digit(long nbr, char *str, int base);
int	ft_print_str(char *str);
int	ft_validate_specif(const char specif);
int	ft_print_pointer(va_arg(ap, void *), BASE10, 16);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		is_specif;

	count = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		
		if (*format == '%')
		{
			is_specif = ft_validate_specif(*(++format));
			if (is_specif == 1)
				count += ft_print_format(*format, ap);
			else
				return ft_printf("Error!\n");
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

int	ft_validate_specif(const char specif)
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

int	ft_print_format(const char specifier, va_list ap)
{
	int count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'i' || specifier == 'd')
		count += ft_print_digit(va_arg(ap, int), BASE10, 10);
	else if (specifier == 'u')
		count += ft_print_digit(va_arg(ap, int), BASE10, 10);
	//else if (specifier == 'p')
	//	count += ft_print_pointer(va_arg(ap, void *), BASE10, 16);
	else if (specifier == 'x')
		count += ft_print_digit(va_arg(ap, unsigned int), BASE10, 16);
	else if (specifier == 'X')
		count += ft_print_digit(va_arg(ap, unsigned int), BASE16CAP, 16);
	else if (specifier == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		ft_print_char(str[count]);
		count++;
	}
	return (count);
}

int	ft_print_digit(long nbr, char *str, int base)
{
	int 	count;

	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		count += ft_print_digit(-nbr, str, base);
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


int	main()
{
	int count;
                                                    
	count = ft_printf("%%ft_printf: %X\n", 105);
	ft_printf("Count is: %d\n", count);
	count = printf("%%printf: %X\n", 105);
	printf("Count is: %d\n", count);
	return (0);
}
