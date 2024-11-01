/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:27:16 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/01 11:02:22 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*de;
	const char	*sr;

	if (!dest && !src && n > 0)
		return (NULL);
	de = (char *)dest;
	sr = (const char *)src;
	if (de < sr)
	{
		while (n--)
		{
			*de = *sr;
			de++;
			sr++;
		}
	}
	else
	{
		while (n--)
		  *(de + n)  = *(sr + n);
	}
	return ((void *)dest);
}
