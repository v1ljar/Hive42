/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:46:51 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 12:08:28 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1)
	{
		if (str1[i] == str2[i])
			i++;
		else
			break ;
	}
	return (str1[i] - str2[i]);
}
/*
int	main(void)
{
	const char str1[] = "String1";
	const char str2[] = "StringA";
	int	res;

	res = ft_memcmp(str1, str2, 7);
	if (res == 0)
		printf("String are the same!\n");
	else if (res < 0)
		printf("DIFFERENCE! '%i' String1 is less than String2!\n", res);
	else
		printf("DIFFERENCE! '%i' String1 is grater than String2!\n", res);
	return (0);
}
*/
