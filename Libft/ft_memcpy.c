/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:13:07 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 17:42:26 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*des;
	const unsigned char	*sr;

	if (!src && !dest)
		return ('\0');
	i = 0;
	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	while (i < n && sr[i] != '\0')
	{
		des[i] = sr[i];
		i++;
	}
	return (dest);
}
