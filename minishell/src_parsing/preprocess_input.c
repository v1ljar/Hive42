/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:17:09 by vuljas            #+#    #+#             */
/*   Updated: 2025/03/06 18:17:14 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* init_strings is for initializing the strings to lower the number of lines in
 preprocessing_input function */
static int	init_strings(char **input, char **buf, char **res, t_master *mini);
/* handle_open_pipe is handleing opened pipe, gives prompt back */
static int	handle_open_pipe(char **buf, char **res, t_master *mini);
/* clear_extra_scpaces changes 't', '\n', '\r' into space and cleans the
consecutive spaces */
static int	clear_extra_spaces(char **res, char *buf, int *i, int *j);

int	preprocessing_input(t_master *mini, int i)
{
	char	*buf;
	char	*res;
	int		j;

	if (init_strings(&mini->input, &buf, &res, mini) == -2)
		return (-2);
	if (!buf || !res)
		return (-1);
	j = 0;
	while (buf[i] != '\0')
	{
		if (clear_extra_spaces(&res, buf, &i, &j) == -1)
		{
			mini->wstatus = 2;
			return (-2);
		}
	}
	res[j] = '\0';
	free(buf);
	if (res && res[0] != '\0')
		add_history(res);
	mini->input = NULL;
	mini->cleaned = res;
	return (0);
}

static int	init_strings(char **input, char **buf, char **res, t_master *mini)
{
	int	open_pipe_res;

	*buf = ft_strtrim(*input, " ");
	free(*input);
	*input = NULL;
	if (!*buf)
		return (-1);
	if (buf[0][0] != '|' && valid_open_pipe(*buf, 0, mini, 0) == 1)
	{
		rl_event_hook = (void *)signal_handler_rl;
		open_pipe_res = handle_open_pipe(buf, res, mini);
		if (open_pipe_res != 0)
			return (open_pipe_res);
	}
	else
	{
		*res = ft_calloc(ft_strlen(*buf) + 1, 1);
		if (!*res)
		{
			free(*buf);
			*buf = NULL;
			return (-1);
		}
	}
	return (0);
}

static int	handle_open_pipe(char **buf, char **res, t_master *mini)
{
	char	*str;
	char	*full_str;

	str = readline("> ");
	if (g_signal == SIGINT)
		return (free_n_continue(buf, mini));
	if (!str)
	{
		free(*buf);
		*buf = NULL;
		return (mini_error(NULL, NULL, "syntax error: unexpected end of file"
				, -1));
	}
	else
	{
		full_str = ft_strjoin(*buf, str);
		free(*buf);
		free(str);
		if (!full_str)
			return (-1);
		init_strings(&full_str, buf, res, mini);
	}
	return (0);
}

static int	clear_extra_spaces(char **res, char *buf, int *i, int *j)
{
	if (buf[*i] == '"' || buf[*i] == '\'')
	{
		if (handle_quote(res, buf, i, j) == -1)
			return (-1);
	}
	else if (buf[*i] == '\t' || buf[*i] == '\n' || buf[*i] == '\r')
		buf[*i] = ' ';
	else if (buf[*i] == ' ' && (*j > 0 && (*res)[(*j) - 1] == ' '))
		(*i)++;
	else if ((*j > 0 && buf[*i] == '|' && (*res)[*j - 1] == '|') || (*j > 1
		&& buf[*i] == '|' && (*res)[*j - 1] == ' ' && (*res)[*j - 2] == '|'))
	{
		free(buf);
		free(*res);
		return (mini_error(NULL, NULL, "syntax error near unexpected token `|'"
				, -1));
	}
	else
		(*res)[(*j)++] = buf[(*i)++];
	return (0);
}

int	handle_quote(char **res, char *buf, int *i, int *j)
{
	char	c;

	c = buf[*i];
	(*res)[(*j)++] = buf[(*i)++];
	while (buf[*i] != '\0' && buf[*i] != c)
		(*res)[(*j)++] = buf[(*i)++];
	if (buf[*i] == '\0')
	{
		ft_putstr_fd("Minishell: syntax error: unclosed quote\n", 2);
		free(*res);
		free(buf);
		return (-1);
	}
	(*res)[(*j)++] = buf[(*i)++];
	return (0);
}
