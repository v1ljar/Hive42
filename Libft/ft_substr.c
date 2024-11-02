/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:09 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/02 14:02:37 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\0')
	{
		if (i == start)
		{
			j = 0;
			res = malloc(sizeof(char) * (len + 1));
			if (res == NULL)
				return (NULL);
			while (s[i] != '\0' && j < len)
				res[j++] = s[i++];
			res[j] = '\0';
			return (res);
		}
		i++;
	}
	return (NULL);
}
