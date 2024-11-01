/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:41 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/30 15:31:15 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	while (*s && i < len)
	{
		if (s[len - i] == c)
			return ((char *)s + (len - i));
		i++;
	}
	if (c == '\0')
		return ((char *)s + (len + 1));
	return (NULL);
}
/*
int	main(void)
{
	char str[] = "This is the test String";
	char *s;
	char c = 'u';

	s = ft_strrchr(str, c);
	if (s)
		printf("The last occurance of %c is: %s", c, s);
	else
		printf("No occurance of %c in:  %s\n", c, str);
	return (0);
}
*/
