/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:22:19 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/29 16:11:26 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*x;
	int				i;

	i = 0;
	x = (unsigned char *)s;
	while (n > 0)
	{
		x[i++] = c;
		n--;
	}
	return ((void *)x);
}
