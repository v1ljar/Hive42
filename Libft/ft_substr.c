/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:28:09 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/13 16:02:21 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate_sub(char const *s, size_t len, size_t i);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
  	size_t actual_len;

	if (!s)
		return (NULL);
	actual_len = ft_strlen(s);
	if (actual_len < start)
		return (ft_strdup(""));
	if (actual_len - start < len)
		len = actual_len - start;
	return (ft_allocate_sub(s, len, start));
}

static char	*ft_allocate_sub(char const *s, size_t len, size_t i)
{
	char	*res;
	size_t	j;
	
	res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	while (s[i] != '\0' && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}

