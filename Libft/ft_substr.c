/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:09 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/07 10:08:05 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate_sub(char const *s, size_t len, size_t i);
static char	*ft_return_empty(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (i == start)
		{
			res = ft_allocate_sub(s, len, i);
			if (res == NULL)
				return (NULL);
			return (res);
		}
		i++;
	}
	if (i < start)
	{
		res = ft_return_empty();
		return (res);
	}
	return (NULL);
}

static char	*ft_allocate_sub(char const *s, size_t len, size_t i)
{
	char	*res;
	size_t	j;

	j = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (s[i] != '\0' && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}

static char	*ft_return_empty(void)
{
	char	*res;

	res = malloc(sizeof(char) * 1);
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	return (res);
}
