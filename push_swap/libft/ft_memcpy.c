/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:13:07 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/08 10:41:44 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*des;
	const unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	if (n == 0 || (dest == src))
		return (dest);
	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	while (n)
	{
		if (*des != *sr)
			*des = *sr;
		des++;
		sr++;
		n--;
	}
	return (dest);
}
