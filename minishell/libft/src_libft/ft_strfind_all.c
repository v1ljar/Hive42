/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:05:42 by jpiensal          #+#    #+#             */
/*   Updated: 2025/02/12 17:06:20 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strfind_all(const char *str, const char c)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	while (str[i])
	{
		if (str[i] == c)
			occ++;
		i++;
	}
	return (occ);
}
