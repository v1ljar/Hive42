/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:54:25 by vuljas            #+#    #+#             */
/*   Updated: 2024/10/31 15:24:51 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	res = malloc(size * nmemb);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < (size * nmemb))
		res[i++] = 0;
	return (res);
}
