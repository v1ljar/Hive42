/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:35:37 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/26 17:52:21 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*result;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*des;
	const unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	if (n == 0 || (dest == src))
		return (dest);
	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	while (n)
	{
		if (*des != *sr)
			*des = *sr;
		des++;
		sr++;
		n--;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, s2, s2_len);
	res[s1_len + s2_len] = '\0';
	return (res);
}

ft_next_line(fd, buf, is_valid)

char	*ft_check_line(int fd)
{
	size_t		len;
	char*		result;
	static char *buf;
	int			is_valid;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	len = read(fd, buf, BUFFER_SIZE);
	buf[len] = '\0';
	is_valid = 0;
	while (is_valid == 0)
	{
		ft_next_line(fd, buf, is_valid);
	}
	else
		return (result);
}
