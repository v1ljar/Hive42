/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:27:16 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/08 13:28:10 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*de;
	const char	*sr;

	if (!dest || !src)
		return (NULL);
	if (src == dest)
		return (dest);
	de = (char *)dest;
	sr = (const char *)src;
	if (sr < de && sr + n > de)
	{
		while (n--)
			*(de + n) = *(sr + n);
	}
	else
	{
		while (n--)
		{
			*de = *sr;
			de++;
			sr++;
		}
	}
	return (dest);
}
