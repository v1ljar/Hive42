/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_peek_nextchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:30:26 by jpiensal          #+#    #+#             */
/*   Updated: 2025/03/28 10:36:16 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_peek_nextchr(const char c, const char *to_peek)
{
	size_t	i;

	i = 0;
	while (to_peek[i])
	{
		if (to_peek[i] == c)
			return (1);
		i++;
	}
	return (0);
}
