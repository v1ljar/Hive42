/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:28:38 by jpiensal          #+#    #+#             */
/*   Updated: 2025/01/17 11:11:35 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	malloc_word(char **split, int idx, int len)
{
	int	i;

	i = 0;
	split[idx] = malloc(sizeof(char) * len + 1);
	if (!split[idx])
	{
		while (i <= idx)
			free(split[i++]);
		free(split);
		return (1);
	}
	return (0);
}

static int	store_words(char **split, const char *str, char c, int word_count)
{
	int	i;
	int	j;
	int	idx;
	int	start;

	i = 0;
	idx = 0;
	while (i < word_count)
	{
		j = 0;
		while (str[idx] == c && str[idx])
			idx++;
		start = idx;
		while (str[idx] != c && str[idx])
			idx++;
		if (malloc_word(split, i, (idx - start)))
			return (1);
		while (start < idx)
			split[i][j++] = str[start++];
		split[i++][j] = '\0';
	}
	split[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_count;

	word_count = count_words(s, c);
	if (word_count == 0 || !s)
		return (NULL);
	split = malloc(sizeof(char *) * (word_count + 1));
	if (!split)
		return (NULL);
	if (store_words(split, s, c, word_count))
		return (NULL);
	return (split);
}
