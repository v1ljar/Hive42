/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:10 by jpiensal          #+#    #+#             */
/*   Updated: 2025/01/22 16:55:25 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*calloc;
	size_t			i;
	size_t			total;

	total = nmemb * size;
	if (nmemb && total / nmemb != size)
		return (NULL);
	calloc = malloc(total);
	if (!calloc)
		return (NULL);
	i = 0;
	while (i < total)
		calloc[i++] = 0;
	return (calloc);
}
