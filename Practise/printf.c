#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_print_str(char *str);
int	ft_print_digit(long nbr);

int ft_printf(const char *str, ... )
{
	va_list	ap;
	int		result;
	int		i;

	result = 0;
	va_start(ap, str);
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[++i] == 's')
				result += ft_print_str(va_arg(ap, char *));
			else if (str[i] == 'd')
				result += ft_print_digit(va_arg(ap, long));
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return result;
}

int	ft_print_str(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i++], 1);
		result++;
	}
	return result;
}

int	ft_print_digit(long nbr)
{
	int		neg;
	char	base[16] = "0123456789abcdef";
	int		result;

	result = 0;
	neg = 1;
	if (nbr < 0)
	{
		neg = -1;
		write(1, "-", 1);
		nbr *= -1;
		result++;
	}
	if (nbr > 9)
	{
		result += ft_print_digit(nbr % 10);
		nbr /= 10;
	}
	result += write(1, &base[nbr], 1);
	return result * neg;
}

int main()
{
	//printf("%d", ft_printf("Hello %s\n", "toto"));
	printf("\n%d\n", ft_printf("HELLOs%d", 42));
	//ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	return 0;
}