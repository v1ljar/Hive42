/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:12:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:51:43 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static void	exec_commands(t_master *mini, char **env);
static int	exec_cmd(t_master *mini, t_cmd *cmd, char **env);
static int	exec_builtin(t_master *mini, t_cmd *cmd);
static int	heredoc_handler(t_master *mini, t_cmd *cmd);

int	mini_exec(t_master *mini)
{
	char	**env;

	if (heredoc_handler(mini, mini->root_cmd))
		return (-1);
	mini->wstatus = set_redirections(mini->root_cmd);
	if (mini->root_cmd->next == NULL
		&& is_builtin((const char **)mini->root_cmd->cmd))
	{
		if (!dup_fd(mini->root_cmd))
			mini->wstatus = exec_builtin(mini, mini->root_cmd);
	}
	else
	{
		env = cpy_lst_to_arr(&mini->env);
		if (!env)
			return (1);
		exec_commands(mini, env);
		ft_delarray(env);
	}
	return (0);
}

static void	exec_commands(t_master *mini, char **env)
{
	t_cmd	*cmd;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	cmd = mini->root_cmd;
	while (cmd)
	{
		while (cmd && cmd->io_error == true && !close_fd(cmd))
			cmd = cmd->next;
		if (!cmd || set_io_in(cmd, mini->temp_io))
			return ;
		if (cmd->next && create_pipe(cmd))
			return ;
		if (set_io_out(cmd, mini->temp_io))
			return ;
		mini->pid = fork();
		if (mini->pid == -1)
			mini_error(NULL, NULL, NULL, 0);
		else if (mini->pid == 0)
			exec_cmd(mini, cmd, env);
		cmd = cmd->next;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	wait_loop(mini, false, 0);
}

static int	exec_cmd(t_master *mini, t_cmd *cmd, char **env)
{
	close(mini->temp_io[0]);
	close(mini->temp_io[1]);
	if (cmd->next && cmd->next->fdin != -1)
		close(cmd->next->fdin);
	if (!cmd->cmd)
		exit(0);
	if (is_builtin((const char **)cmd->cmd))
		exit(exec_builtin(mini, cmd));
	execve(cmd->path, cmd->cmd, env);
	command_error(cmd->cmd[0]);
	exit(0);
}

static int	exec_builtin(t_master *mini, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(cmd->cmd[0], "export", 7))
		ret = mini_export(mini->env, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		ret = mini_unset(mini, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		ret = mini_cd(mini, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		ret = mini_pwd(mini);
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		ret = mini_env(&mini->env, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		ret = mini_exit(mini, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		ret = mini_echo(&(cmd->cmd[1]));
	return (ret);
}

static int	heredoc_handler(t_master *mini, t_cmd *cmd)
{
	t_file	*temp;

	while (cmd)
	{
		temp = cmd->infile;
		while (temp)
		{
			if (temp->type == '+')
			{
				if (create_heredoc(mini, cmd, temp))
					return (-1);
			}
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
