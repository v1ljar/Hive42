/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:17:39 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/21 16:07:00 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	main(void)
{
	int		count1;
	int		count2;
	int		i;
	char	*str;
	void	*ptr;

	ft_printf("\n\t\t**********Printf test**********\n\n");
	ft_printf("\t*____________*\n\t| Testing %%s |");
	str = "Testing out printf with specifier s!";
	ft_printf("\tString is: %s", str);
	ft_printf("\n\t*************\n");
	ft_printf("\tft_printf: ");
	count1 = ft_printf("%s\n", str);
	ft_printf("\tCount is: %d\n", count1);
	ft_printf("\tprintf: ");	
	count2 = printf("%s\n", str);
	printf("\tCount is: %d\n", count2);
	if (count1 == count2)
		ft_printf("\t\t\tSUCCESS!\n\n");
	else
		ft_printf("\t\t\tFAILED!\n\n");

	ft_printf("\n\t\t********************\n\n");
	ft_printf("\t*___________________*\n\t| Testing %%i and %%d |");
	i = 42;
	ft_printf("\tNbr: %i", i);
	ft_printf("\n\t*********************\n");
	ft_printf("\tft_printf: ");
	count1 = ft_printf("%i\n", i);
	ft_printf("\tCount is: %d\n", count1);
	ft_printf("\tprintf: ");	
	count2 = printf("%i\n", i);
	printf("\tCount is: %d\n", count2);
	if (count1 == count2)
		ft_printf("\t\t\tSUCCESS!\n");
	else
		ft_printf("\t\t\tFAILED!\n\n");

		ft_printf("\n\t\t********************\n\n");
	ft_printf("\t*____________*\n\t| Testing %%p |");
	i = 42;
	ptr = &i;
	ft_printf("\tPointer: %p", ptr);
	ft_printf("\n\t**************\n");
	ft_printf("\tft_printf: ");
	count1 = ft_printf("%p\n", ptr);
	ft_printf("\tCount is: %d\n", count1);
	ft_printf("\tprintf: ");	
	count2 = printf("%p\n", ptr);
	printf("\tCount is: %d\n", count2);
	if (count1 == count2)
		ft_printf("\t\t\tSUCCESS!\n");
	else
		ft_printf("\t\t\tFAILED!\n\n");

	ft_printf("\n\t\t********************\n\n");
	ft_printf("\t*____________*\n\t| Testing %%x |");
	i = 123456789;
	ft_printf("\tHexadecimal of %i", i);
	ft_printf("\n\t**************\n");
	ft_printf("\tft_printf: ");
	count1 = ft_printf("%x\n", i);
	ft_printf("\tCount is: %d\n", count1);
	ft_printf("\tprintf: ");	
	count2 = printf("%x\n", i);
	printf("\tCount is: %d\n", count2);
	if (count1 == count2)
		ft_printf("\t\t\tSUCCESS!\n");
	else
		ft_printf("\t\t\tFAILED!\n\n");

	ft_printf("\n\t\t********************\n\n");
	ft_printf("\t*____________*\n\t| Testing %%X |");
	i = -42;
	ft_printf("\tHexadecimal of %i", i);
	ft_printf("\n\t**************\n");
	ft_printf("\tft_printf: ");
	count1 = ft_printf("%X\n", i);
	ft_printf("\tCount is: %d\n", count1);
	ft_printf("\tprintf: ");	
	count2 = printf("%X\n", i);
	printf("\tCount is: %d\n", count2);
	if (count1 == count2)
		ft_printf("\t\t\tSUCCESS!\n");
	else
		ft_printf("\t\t\tFAILED!\n\n");
	
	return (0);
}
