/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:41 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/14 13:37:15 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[len - i - 1] == (char)c)
			return ((char *)s + (len - i - 1));
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
