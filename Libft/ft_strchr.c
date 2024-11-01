/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:13:36 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/30 15:34:59 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
/*
int	main(void)
{
	const char str[] = "Test String here";
	char c = 'u';
	char *res;

	res = ft_strchr(str, c);
	if (res)
		printf("First occurance of %c is: %s", c, res);
	else
		printf("No occurance of %c in: %s", c, str);
	return (0);
}
*/
