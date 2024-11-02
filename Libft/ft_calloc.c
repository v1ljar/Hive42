/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:54:25 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/02 10:47:49 by vuljas           ###   ########.fr       */
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
<<<<<<< HEAD
	while (i < (nmemb * size))
=======
	while (i < (size * nmemb))
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
		res[i++] = 0;
	return (res);
}
