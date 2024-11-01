/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:54:25 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 15:24:51 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(size) * nmemb);
	if (res == NULL)
		return (res);
	i = 0;
	while (i < nmemb)
		res[i++] = '0';
	return ((void *)res);
}
/*
int	main(void)
{
	char	*p;
	char	str[] = "123456";
	int 	i;

	p = calloc((ft_strlen(str) + 1), 1);
	i = 0;
	while (str[i] != '\0')
	{
		p[i] = str[i];
		i++;
	}
	printf("Allocated memory content is: %s\n", p);
	free(p);
	return (0);
}
*/
