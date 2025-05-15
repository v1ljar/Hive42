/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_handle_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:03:53 by vuljas            #+#    #+#             */
/*   Updated: 2025/03/12 16:03:57 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function for the extract_word, it counts the length of the word
 to be extracted, length is stored in len variable, that is modifyable,
 because it is as int * parameter. */
static void	extract_word_length(char *str, int *i, int *len);
/* Helper function for process_word, if environment variable, if
 envv ($....), it uses extract_envv_quotes to expand envv, content
 between "..." will be placed into char **buf. */
static void	handle_double_quotes(t_master *mini, char **buf, int *i,
				int *j);

char	*extract_word(char *str, int *i)
{
	char	*res;
	int		start;
	int		len;

	start = *i;
	len = 0;
	while (str[(*i)] != '\0' && str[(*i)] != ' ' && !is_operator(str[(*i)]))
		extract_word_length(str, i, &len);
	if (len == 0)
		return (NULL);
	res = ft_substr(str, start, len);
	if (!res)
		return (NULL);
	else
		return (res);
}

static void	extract_word_length(char *str, int *i, int *len)
{
	char	c;

	if (str[(*i)] == '{' || str[(*i)] == '\'' || str[(*i)] == '"')
	{
		if (str[(*i)] == '{')
			c = '}';
		else
			c = str[*i];
		(*i)++;
		(*len)++;
		while (str[(*i)] != '\0' && str[(*i)] != c)
		{
			(*len)++;
			(*i)++;
		}
		(*len)++;
		(*i)++;
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}

char	*process_word(char *str, t_master *mini, int i, int j)
{
	char	*buf;
	char	*save;

	save = mini->cleaned;
	mini->cleaned = str;
	buf = ft_calloc(ft_strlen(str) + 5000, 1);
	if (!buf)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			handle_single_quotes(str, &buf, &i, &j);
		else if (str[i] == '"')
			handle_double_quotes(mini, &buf, &i, &j);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'
				|| str[i + 1] == '"' || str[i + 1] == '\''))
			extract_envv_quotes(mini, &buf, &i, &j);
		else
			j = check_tilde_add_to_buf(buf, str, &i, mini);
	}
	mini->cleaned = save;
	save = ft_strdup(buf);
	free(buf);
	return (save);
}

void	handle_single_quotes(char *str, char **buf, int *i, int *j)
{
	char	c;

	c = str[(*i)];
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != c)
	{
		(*buf)[(*j)] = str[(*i)];
		(*j)++;
		(*i)++;
	}
	if (str[(*i)] != '\0')
		(*i)++;
}

static void	handle_double_quotes(t_master *mini, char **buf, int *i,
				int *j)
{
	char	c;
	char	*str;

	str = mini->cleaned;
	c = str[*i];
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
	{
		if (str[*i] == '$' && (ft_isalnum(str[*i + 1]) || str[*i + 1] == '?'))
			extract_envv_quotes(mini, buf, i, j);
		else
		{
			(*buf)[(*j)] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	if (str[*i] != '\0')
		(*i)++;
}
