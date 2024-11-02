/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:41 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/01 14:41:37 by vuljas           ###   ########.fr       */
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
		if (s[len - i - 1] == c)
<<<<<<< HEAD
			return ((char *)s + (len - i - 1));
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
=======
			return ((char *)s + (len - i -1));
		i++;
	}
	if (c == '\0')
		return ((char *)s + (len));
>>>>>>> 0ff4ba513d000df9a0bb9ca8b2081ac0ca7f0892
	return (NULL);
}
