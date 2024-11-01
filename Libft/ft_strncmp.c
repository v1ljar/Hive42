/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:53:24 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 10:18:12 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < (n - 1) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
/*
int	main(void)
{
	const char str1[] = "Test1";
	const char str2[] = "Testing";
	int	res;

	res = ft_strncmp(str1, str2, 7);
	if (res == 0)
		printf("Compared strings are the same!\n");
	else if (res < 0)
		printf("STring1 is less than string2!\n");
	else
		printf("STring1 is greater than string2!\n");	
	return (0);
}
*/
