/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:19:20 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 12:07:52 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		x;
	const unsigned char	*str;
	size_t				i;

	x = (unsigned char)c;
	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == x)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char str[] = "This is the test String!";
	char	c = '\0';
	size_t len = 26;
	char	*res;

	res = memchr(str, c, len);
	if (res)
		printf("FOUND! %c occurance is found: %s\n", c, res);
	else
		printf("FAILED!! %c occurance is not found in: %s\n", c, str);
	return (0);
}
*/