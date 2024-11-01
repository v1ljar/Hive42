/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:08:00 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 12:32:34 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if ((dst_len + src_len + 1) > size)
		return (dst_len + src_len + 1);
	i = 0;
	while (((dst_len + i) < size) && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + i + 1);
}
/*
int	main(void)
{
	char	d[50] = "12345678";
	char	d2[20] = "12345";
	char	s[] = "123456789";
	size_t	x;
	size_t	y;

	y = ft_strlcat(d2, s, 10);
	x = ft_strlcat(d, s, 40);
	printf("The length of the concatagnated string is: %li\n", x);
	printf("The concatagnated string is: %s\n", d);
	printf("************************************\n");
	printf("The length of the concatagnated string is: %li\n", y);
	printf("The concatagnated string is: %s\n", d2);
	return (0);
}
*/
