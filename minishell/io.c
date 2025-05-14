/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:06 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/07 16:19:15 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	set_io_in(t_cmd *cmd, int *temp_io)
{
	if (cmd->fdin == -1)
	{
		cmd->fdin = dup(temp_io[0]);
		if (cmd->fdin == -1)
			return (mini_error(NULL, NULL, "Duplication error", 0));
	}
	if (dup2(cmd->fdin, STDIN_FILENO) == -1)
		return (mini_error(NULL, NULL, "Duplication error", 0));
	close(cmd->fdin);
	return (0);
}

int	set_io_out(t_cmd *cmd, int *temp_io)
{
	if (cmd->fdout == -1)
	{
		cmd->fdout = dup(temp_io[1]);
		if (cmd->fdout == -1)
			return (mini_error(NULL, NULL, "Duplication error", 0));
	}
	if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
		return (mini_error(NULL, NULL, "Duplication error", 0));
	close(cmd->fdout);
	return (0);
}

int	open_temp_io(int temp_io[2])
{
	bool	is_error;

	is_error = false;
	temp_io[0] = dup(STDIN_FILENO);
	if (temp_io[0] == -1)
		is_error = true;
	temp_io[1] = dup(STDOUT_FILENO);
	if (temp_io[1] == -1)
		is_error = true;
	if (is_error)
		return (mini_error(NULL, NULL, "Duplication error", 0));
	return (0);
}

int	close_temp_io(int temp_io[2])
{
	bool	is_error;

	is_error = false;
	if (dup2(temp_io[0], STDIN_FILENO) == -1)
	{
		temp_io[0] = -1;
		is_error = true;
	}
	else
		close(temp_io[0]);
	if (dup2(temp_io[1], STDOUT_FILENO) == -1)
	{
		temp_io[1] = -1;
		is_error = true;
	}
	else
		close(temp_io[1]);
	if (is_error)
		return (mini_error(NULL, NULL, "Duplication error", 0));
	return (0);
}
