/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:58 by jpiensal          #+#    #+#             */
/*   Updated: 2024/11/12 12:14:20 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if (size == 0)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = -1;
	if (len_dst >= size)
		return (len_src + size);
	else if (size > (len_dst + len_src))
		while (src[++i] != '\0')
			dst[len_dst + i] = src[i];
	else if (size <= (len_dst + len_src))
		while (++i < (size - len_dst - 1))
			dst[len_dst + i] = src[i];
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}
