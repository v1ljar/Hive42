/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:19:58 by jpiensal          #+#    #+#             */
/*   Updated: 2024/11/13 10:37:55 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen(src);
	i = -1;
	if (!dst || size == 0)
		return (len_src);
	if ((len_src + 1) < size)
		while (src[++i] != '\0')
			dst[i] = src[i];
	else
		while (++i < (size - 1))
			dst[i] = src[i];
	dst[i] = '\0';
	return (len_src);
}
