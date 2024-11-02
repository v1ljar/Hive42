/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:27:16 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/02 10:30:22 by vuljas           ###   ########.fr       */
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
<<<<<<< HEAD
	if (sr < de)
	{
		while (n--)
			*(de + n) = *(sr + n);
	}
	else
=======
	if (de < sr)
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
	{
		while (n--)
		{
			*de = *sr;
			de++;
			sr++;
		}
	}
<<<<<<< HEAD
	return (dest);
=======
	else
	{
		while (n--)
		  *(de + n)  = *(sr + n);
	}
	return ((void *)dest);
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
}
