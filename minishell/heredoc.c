/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:36:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:52:06 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_heredoc(t_master *mini, t_file *file, int *fd, bool is_exp);
static int	process_line(t_master *mini, int *fd, char *line, bool is_expand);
static int	expand_line(t_list *env, char *str, int *fd, bool is_curly);
static int	clean_delimiter(t_file *file, int i, int j, bool *res);

int	create_heredoc(t_master *mini, t_cmd *cmd, t_file *file)
{
	int	res;

	if (pipe(file->herepipe) == -1)
		return (mini_error(NULL, NULL, NULL, 0));
	res = handle_heredoc(mini, file, file->herepipe, true);
	if (res == -2)
		return (-2);
	else if (res == -1)
	{
		close(file->herepipe[0]);
		close(file->herepipe[1]);
		return (-1);
	}
	close(file->herepipe[1]);
	if (cmd->io_error == true)
		close(file->herepipe[0]);
	return (0);
}

static int	handle_heredoc(t_master *mini, t_file *file, int *fd, bool is_exp)
{
	char	*line;

	if (clean_delimiter(file, 0, 0, &is_exp))
		return (-1);
	while (1)
	{
		rl_event_hook = (void *)signal_handler_rl;
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (is_heredoc_signal(mini, fd, line) == -2)
			return (-2);
		if (!line)
			print_warning(file->filename, NULL, NULL, true);
		if (!line || !ft_strcmp(file->filename, line))
			break ;
		if (process_line(mini, fd, line, is_exp))
			return (-1);
	}
	free(line);
	return (0);
}

static int	clean_delimiter(t_file *file, int i, int j, bool *res)
{
	char	*temp;

	if (!ft_strchr(file->filename, '"') && !ft_strchr(file->filename, '\''))
		return (0);
	*res = false;
	temp = ft_calloc(NAME_MAX, sizeof(char));
	if (!temp)
		return (mini_error(NULL, NULL, NULL, 0));
	while (file->filename[i] != '\0' && j < NAME_MAX)
	{
		if (file->filename[i] == '"' || file->filename[i] == '\'')
			handle_single_quotes(file->filename, &temp, &i, &j);
		else
			temp[j++] = file->filename[i++];
	}
	free(file->filename);
	file->filename = temp;
	return (0);
}

static int	process_line(t_master *mini, int *fd, char *line, bool is_expand)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && is_expand)
		{
			if (!ft_strcmp(&line[i], "$?") || !ft_strcmp(&line[i], "${?}"))
			{
				if (print_warning(NULL, mini, fd, false))
					return (-1);
				if (!ft_strncmp(&line[i], "$?", 2))
					i += 2;
				else if (!ft_strncmp(&line[i], "${?}", 4))
					i += 4;
			}
			else
				i += expand_line(mini->env, &line[i], fd, false);
		}
		if (line[i])
			write(fd[1], &line[i++], 1);
	}
	write(fd[1], "\n", 1);
	free(line);
	return (0);
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
	var = find_envv(&env, temp);
	if (var)
		write(fd[1], var, ft_strlen(var));
	if (is_curly)
		return (i + 3);
	return (i + 1);
}
