/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:02:16 by vuljas            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/10 15:44:02 by vuljas           ###   ########.fr       */
=======
/*   Updated: 2024/11/07 11:40:13 by vuljas           ###   ########.fr       */
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c);
static char	**ft_allocate_strings(char **result, char const *str, char c);
static char	*ft_substring(char const *str, int start, int len);
<<<<<<< HEAD
static void	ft_check_subs(char **result, int i);
=======
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = ft_allocate_strings(res, s, c);
	if (!res)
	{
		while (words >= 0)
			free(res[words--]);
		free(res);
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
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	**ft_allocate_strings(char **result, char const *s, char c)
{
	int	len;
	int	start;
	int	i;

	len = 0;
	i = 0;
	while (s[len])
	{
<<<<<<< HEAD
		while (s[len] == c && s[len] != '\0')
			len++;
		start = 0;
		while (s[len] != c && s[len] != '\0')
		{
			len++;
			start++;
		}
		if (start > 0)
		{
			result[i] = ft_substring(s, len - start, start);
			ft_check_subs(result, i);
			i++;
=======
		while (s[i] == c && s[i] != '\0')
			i++;
		j = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			j++;
		}
		if (j > 0)
		{
			result[k] = ft_substring(s, i - j, j);
			k++;
>>>>>>> 338b55019fff64a411233e65d8a8b1c09a21950b
		}
	}
	result[i] = NULL;
	return (result);
}

static char	*ft_substring(char const *str, int start, int len)
{
	char	*res;
	int		count;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	count = 0;
	while (count < len)
	{
		res[count] = str[start + count];
		count++;
	}
	res[len] = '\0';
	return (res);
}

static void	ft_check_subs(char **result, int i)
{
	int	count;

	count = 0;
	while (count <= i)
	{
		if (!result[i])
		{
			while (i >= 0)
			{
				free(result[i]);
				i--;
			}
		}
		count++;
	}
}
