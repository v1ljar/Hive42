/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:36:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 12:02:18 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_warning(char *limiter);
static void	process_line(t_list *env, int *fd, char *line, bool is_expand);
static int	expand_line(t_list *env, char *str, int *fd, bool is_curly);
static bool	clean_delimiter(t_file *file, t_master *mini);

int	handle_heredoc(t_list *env, t_file *file, int *fd, t_master *mini)
{
	static char	*line;
	bool		is_expand;

	is_expand = clean_delimiter(file, mini);
	while (1)
	{
		rl_event_hook = (void *)exec_signals_handler;
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (is_heredoc_signal(mini, fd, line) == -2)
			return (-2);
		if (!line || !ft_strcmp(file->filename, line))
		{
			if (!line)
				print_warning(file->filename);
			break ;
		}
		process_line(env, fd, line, is_expand);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (0);
}

static bool	clean_delimiter(t_file *file, t_master *mini)
{
	char	*new;
	bool	res;

	res = false;
	if (!ft_strchr(file->filename, '"') && !ft_strchr(file->filename, '\''))
	{
		if (ft_strchr(file->filename, '$'))
			res = true;
		else
			return (true);
	}
	new = extract_quotes(file->filename, mini, 0, 0);
	free(file->filename);
	file->filename = new;
	return (res);
}

static void	process_line(t_list *env, int *fd, char *line, bool is_expand)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && is_expand)
			i += expand_line(env, &line[i], fd, false);
		write(fd[1], &line[i++], 1);
	}
	write(fd[1], "\n", 1);
}

static int	expand_line(t_list *env, char *str, int *fd, bool is_curly)
{
	static char	temp[PATH_MAX];
	char		*var;
	int			i;

	str++;
	if (!ft_isalnum(*str) && *str != '_' && *str != '{')
		return (0);
	if (*str == '{')
	{
		str++;
		is_curly = true;
	}
	i = 0;
	while (*str && (ft_isalnum(*str) || *str == '_'))
		temp[i++] = *str++;
	if (is_curly && *str != '}')
		return (0);
	temp[i] = '\0';
	var = find_envv(env, temp);
	if (var)
		write(fd[1], var, ft_strlen(var));
	if (is_curly)
		return (i + 3);
	return (i + 1);
}

static void	print_warning(char *limiter)
{
	ft_putstr_fd("Minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}
