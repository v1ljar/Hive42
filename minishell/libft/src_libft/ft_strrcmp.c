/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:19:48 by jpiensal          #+#    #+#             */
/*   Updated: 2025/01/31 13:53:15 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (-1);
	if (!s2 || !s2[0])
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (j > i)
		return (-1);
	while (j-- > 0)
	{
		if (s1[--i] != s2[j])
			return (-1);
	}
	return (0);
}
