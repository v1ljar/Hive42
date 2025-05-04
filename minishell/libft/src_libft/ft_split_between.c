/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_between.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:58:55 by jpiensal          #+#    #+#             */
/*   Updated: 2025/02/26 15:50:07 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(const char *str, char sp1, char sp2)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		while (str[i] == sp1 && str[i])
			i++;
		if (!str[i])
			return (word_count);
		else if (str[i] == sp2)
		{
			while (str[++i] != sp2)
				if (str[i] == '\0')
					return (0);
			i++;
		}
		else
			while (str[i] != sp1 && str[i])
				i++;
		word_count++;
	}
	return (word_count);
}

static int	word_len(const char *str, char sp1, char sp2)
{
	int	len;

	len = 0;
	if (*str == sp2)
	{
		str++;
		if (*str == sp2)
			return (0);
		while (*str++ != sp2)
			len++;
	}
	else
		while (str[len] != sp1 && str[len])
			len++;
	return (len);
}

static char	*add_word(char *str, char sp1, char sp2)
{
	char	*new_word;
	int		len;
	int		i;

	len = word_len(str, sp1, sp2);
	new_word = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_word)
		return (NULL);
	i = 0;
	if (*str == sp2)
		str++;
	if (*str != sp2)
	{
		while (i < len)
			new_word[i++] = *str++;
	}
	new_word[i] = '\0';
	return (new_word);
}

static char	**add_words_to_arr(char **arr, char *str, char sp1, char sp2)
{
	int	i;
	int	j;

	i = 0;
	while (*str)
	{
		j = 0;
		while (*str == sp1 && *str)
			str++;
		if (*str == '\0')
			break ;
		arr[i] = add_word(str, sp1, sp2);
		if (!arr[i])
		{
			ft_delarray(arr);
			return (NULL);
		}
		if (*str == sp2)
			str += 2;
		while (arr[i][j++])
			str++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_between(char *str, char sp1, char sp2)
{
	char	**arr;
	int		word_count;

	if (!str || !sp1 || !sp2)
		return (NULL);
	word_count = count_words(str, sp1, sp2);
	if (word_count == 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	arr = add_words_to_arr(arr, str, sp1, sp2);
	return (arr);
}
