/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:34:55 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/01 11:54:02 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (accept[j] && accept[j] != str[i])
			j++;
		if (accept[j] == '\0')
			return (count);
		count++;
		i++;
	}
	return (count);
}
