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

static int	ft_count_words(const char *s, char c);
static char	**ft_allocate_strings(char **result, const char *str, char c);
static char	*ft_substring(const char *s, int start, int len);

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		words;

	if (!s)
	  return (NULL);
	words = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	if (!ft_allocate_strings(res, s, c))
	{
		free(res);
		return (NULL);
	}
	return (res);
}

static int	ft_count_words(const char *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
	  while (s[i] == c)
	    i++;
	  if (s[i] != c && s[i] != '\0')
	  {
	    count++;
	    while (s[i] != c && s[i] != '\0')
	      i++;
	  }
	}
	return (count);
}

static char	**ft_allocate_strings(char **result, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > j)
		{
			result[k] = ft_substring(s, j, i - j);
			if (!result[k])
			{
				while (k >= 0)
		  			free(result[--k]);		    
				free(result);
				return (NULL);
			}
			k++;
		}
	}
	result[k] = NULL;
	return (result);
}

static char	*ft_substring(const char *s, int start, int len)
{
	char	*res;
	int	count;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	count = 0;
	while (count < len)
	{
		res[count] = s[start + count];
		count++;
	}
	res[len] = '\0';
	return (res);
}
