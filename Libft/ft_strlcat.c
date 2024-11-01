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

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && size == 0)
	  	return (src ? ft_strlen(src) : 0);
	if (!src && size == 0)
	  	return (dst ? ft_strlen(dst) : 0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
	  	return (size + src_len);
	i = 0;
	while ((dst_len + i + 1) < size && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if ((dst_len + i) < size)
	  	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
