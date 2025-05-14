/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:06 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/08 17:31:40 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_error(char *cmd, char *filename, char *err_str, int err_no)
{
	ft_putstr_fd("Minishell: ", 2);
	if (cmd)
	{
		if (!*cmd)
			ft_putstr_fd("''", 2);
		else
			ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err_no == 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putendl_fd(err_str, 2);
	return (err_no);
}

void	command_error(char *cmd)
{
	struct stat	info;

	if (stat(cmd, &info))
		exit(mini_error(cmd, NULL, "Command not found", 127));
	else if (S_ISDIR(info.st_mode))
		exit(mini_error(cmd, NULL, "Is a directory", 126));
	else if (!(info.st_mode & S_IXUSR))
		exit(mini_error(cmd, NULL, "Permission denied", 126));
	else
		exit(mini_error(cmd, NULL, NULL, 0));
}

bool	is_builtin(const char **str)
{
	if (!str)
		return (false);
	if (!ft_strncmp(*str, "export", 7))
		return (true);
	else if (!ft_strncmp(*str, "unset", 6))
		return (true);
	else if (!ft_strncmp(*str, "cd", 3))
		return (true);
	else if (!ft_strncmp(*str, "pwd", 4))
		return (true);
	else if (!ft_strncmp(*str, "env", 4))
		return (true);
	else if (!ft_strncmp(*str, "exit", 5))
		return (true);
	else if (!ft_strncmp(*str, "echo", 5))
		return (true);
	return (false);
}

void	del_content(void *content)
{
	size_t	len;

	len = ft_strlen((char *)content);
	ft_memset(content, 0, len);
	free(content);
}

int	close_fd(t_cmd *cmd)
{
	if (cmd->fdin != -1)
		close(cmd->fdin);
	if (cmd->fdout != -1)
		close(cmd->fdout);
	return (0);
}
