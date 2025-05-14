/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:54:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/08 15:04:22 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_files(t_cmd *cmd, t_file *file, int *current_fd, int in_out)
{
	if (in_out == 0)
	{
		if (file->type == '+')
			*current_fd = file->herepipe[0];
		else
			*current_fd = open(file->filename, O_RDONLY);
	}
	else
	{
		if (file->type == '+')
			*current_fd = open(file->filename, O_WRONLY | O_CREAT
					| O_APPEND, 00644);
		else
			*current_fd = open(file->filename, O_WRONLY | O_CREAT
					| O_TRUNC, 00644);
	}
	if (*current_fd == -1)
		cmd->io_error = mini_error(NULL, file->filename, NULL, 0);
	else if (file->next)
		close(*current_fd);
	return (cmd->io_error);
}

int	set_redirections(t_cmd *cmd)
{
	t_file	*temp;
	int		ret;

	ret = 0;
	while (cmd)
	{
		temp = cmd->infile;
		while (temp && !cmd->io_error)
		{
			if (open_files(cmd, temp, &cmd->fdin, 0))
				break ;
			temp = temp->next;
		}
		temp = cmd->outfile;
		while (temp && !cmd->io_error)
		{
			if (open_files(cmd, temp, &cmd->fdout, 1))
				break ;
			temp = temp->next;
		}
		ret = cmd->io_error;
		cmd = cmd->next;
	}
	return (ret);
}

int	dup_fd(t_cmd *cmd)
{
	if (cmd->fdin != -1)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (mini_error(NULL, NULL, "Duplication error", 0));
		close(cmd->fdin);
	}
	if (cmd->fdout != -1)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			return (mini_error(NULL, NULL, "Duplication error", 0));
		close(cmd->fdout);
	}
	return (0);
}

int	create_pipe(t_cmd *cmd)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (mini_error(NULL, NULL, NULL, 0));
	if (cmd->fdout == -1)
		cmd->fdout = fd[1];
	else
		close(fd[1]);
	if (cmd->next->fdin == -1)
		cmd->next->fdin = fd[0];
	else
		close(fd[0]);
	return (0);
}
