/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:03:04 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/18 09:49:22 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_front(const char *s1, const char *set);
static size_t	ft_count_end(const char *s1, const char *set, size_t len);
static int		ft_compare(const char s1, const char *set);

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*res;
	size_t	len;
	size_t	offset;
	size_t	end_len;
	size_t	total;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	offset = ft_count_front(s1, set);
	if (offset == len)
	{
		res = ft_calloc(1, 1);
		return (res);
	}
	end_len = ft_count_end(s1, set, len);
	total = len - offset - end_len;
	res = malloc(sizeof(char) * (total + 1));
	if (res == NULL)
		return (NULL);
	res = ft_memcpy(res, s1 + offset, total);
	res[total] = '\0';
	return (res);
}

static size_t	ft_count_front(const char *s1, const char *set)
{
	size_t	total;
	size_t	i;
	int		flag;

	total = 0;
	i = 0;
	while (s1[i])
	{
		flag = ft_compare(s1[i], set);
		if (flag == 1)
		{
			total += 1;
			i++;
		}
		else
			break ;
	}
	return (total);
}

static size_t	ft_count_end(const char *s1, const char *set, size_t len)
{
	size_t	total;
	int		flag;

	total = 0;
	while (len)
	{
		flag = ft_compare(s1[len - 1], set);
		if (flag == 1)
		{
			total += 1;
			len--;
		}
		else
			break ;
	}
	return (total);
}

static int	ft_compare(const char s1, const char *set)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	while (set[j] != '\0')
	{
		if (s1 == set[j])
			return (1);
		j++;
	}
	return (result);
}
