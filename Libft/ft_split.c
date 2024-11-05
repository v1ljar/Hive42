/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:02:16 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/05 16:55:50 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c);
static char	**ft_allocate_strings(char **result, char *str, char c);
static char	*ft_substring(char *res, char *str, int i, int j);

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*trimmed;
	int		words;

	words = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	trimmed = ft_strtrim(s, &c);
	res = ft_allocate_strings(res, trimmed, c);
	if (!res)
	{
		while (words >= 0)
			free(res[words--]);
		return (NULL);
	}
	return (res);
}

static int	ft_count_words(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i - 1] == c || s[i + 1] == '\0' || i == 0))
			i++;
		else if (s[i] == c)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	if (s[i] == '\0' && count == 0)
		count++;
	return (count);
}

static char	**ft_allocate_strings(char **result, char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			j++;
		}
		if (s[i] == c || s[i + 1] == '\0')
		{
			result[k] = ft_substring(result[k], s, i, j);
			i++;
		}
		while (s[i] == c)
			i++;
		k++;
	}
	result[k] = NULL;
	return (result);
}

static char	*ft_substring(char *res, char *str, int i, int j)
{
	int	count;

	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	count = 0;
	while (count < j)
	{
		res[count] = str[i - j + count];
		count++;
	}
	res[j] = '\0';
	return (res);
}
