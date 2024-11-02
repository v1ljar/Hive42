/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:08:00 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/02 11:53:32 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && size == 0)
<<<<<<< HEAD
		return (ft_strlen(src));
	if (!src && size == 0)
		return (ft_strlen(dst));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dst_len)
		return (src_len + size);
	i = 0;
	while ((dst_len + i) < (size - 1) && src[i] != '\0')
=======
	  	return (src ? ft_strlen(src) : 0);
	if (!src && size == 0)
	  	return (dst ? ft_strlen(dst) : 0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
	  	return (size + src_len);
	i = 0;
	while ((dst_len + i + 1) < size && src[i] != '\0')
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
	{
		dst[dst_len + i] = src[i];
		i++;
	}
<<<<<<< HEAD
	dst[dst_len + i] = '\0';
=======
	if ((dst_len + i) < size)
	  	dst[dst_len + i] = '\0';
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
	return (dst_len + src_len);
}
