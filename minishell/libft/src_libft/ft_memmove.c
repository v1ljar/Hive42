/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:19:17 by jpiensal          #+#    #+#             */
/*   Updated: 2024/11/04 10:43:00 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s_dest;
	char	*s_src;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	s_dest = (char *)dest;
	s_src = (char *)src;
	i = 0;
	if (s_src < s_dest)
	{
		while (n-- > 0)
			s_dest[n] = s_src[n];
	}
	else
	{
		while (i < n)
		{
			s_dest[i] = s_src[i];
			i++;
		}
	}
	return (dest);
}
