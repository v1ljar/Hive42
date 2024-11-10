/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:27:16 by vuljas            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/10 12:27:07 by vuljas           ###   ########.fr       */
=======
/*   Updated: 2024/11/08 13:28:10 by vuljas           ###   ########.fr       */
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*de;
	const char	*sr;

<<<<<<< HEAD
	if (!dest && !src)
=======
	if (!dest || !src)
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b
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
