/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:25:20 by jpiensal          #+#    #+#             */
/*   Updated: 2024/11/12 12:26:39 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len_s1;
	char	*new_str;

	i = 0;
	if (!s1)
		return (ft_strdup(""));
	len_s1 = ft_strlen(s1);
	if (!set)
		return ((char *)s1);
	while (check_char(set, s1[i]))
		i++;
	if (s1[i] != '\0')
		while (check_char(set, s1[len_s1 - 1]))
			len_s1--;
	new_str = malloc(sizeof(char) * (len_s1 - i) + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	while (i < len_s1)
		new_str[j++] = s1[i++];
	new_str[j] = '\0';
	return (new_str);
}
