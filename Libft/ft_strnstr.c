/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:18:52 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 12:06:12 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little)
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	str1[] = "This is the TEST string";
	const char	search[] = "TEST";
	char	*res;

	res = ft_strnstr(str1, search, 16);
	if (res)
		printf("Found! '%s' is found in: %s\n", search, res);
	else
		printf("'%s' NOT FOUND IN: %s\n", search, str1);
	return (0);
}
*/
