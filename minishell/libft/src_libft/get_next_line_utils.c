/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:47:08 by jpiensal          #+#    #+#             */
/*   Updated: 2025/01/22 11:18:01 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	uint32_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*gnl_strjoin_n_free(char *s1, const char *s2)
{
	uint32_t	i;
	uint32_t	j;
	char		*str;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*gnl_strdup(const char *str)
{
	int32_t	i;
	char	*ret;

	if (str[0] == '\0')
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (gnl_strlen(str) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
