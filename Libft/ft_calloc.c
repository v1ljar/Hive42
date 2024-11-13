/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:54:25 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/13 15:50:43 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;
	size_t	total;

	total = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb != total / size)
		return (NULL);
	res = malloc(total);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < (total))
		res[i++] = 0;
	return (res);
}
