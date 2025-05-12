/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:12:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 14:19:29 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

static void	exec_commands(t_master *mini, int *temp_io, char **env);
static int	exec_cmd(t_master *mini, t_cmd *cmd, char **env);
static int	exec_builtin(t_master *mini, t_cmd *cmd);
static int	heredoc_handler(t_list *env, t_cmd *cmd, t_master *mini);

int	mini_exec(t_master *mini)
{
	int		temp_io[2];
	char	**env;
	int		heredoc_res;

	handle_temp_io(temp_io, 1);
	heredoc_res = heredoc_handler(mini->env, mini->root_cmd, mini);
	if (heredoc_res != 0)
		return (handle_temp_io(temp_io, 0), heredoc_res);
	mini->wstatus = set_redirections(mini->root_cmd);
	if (mini->root_cmd->next == NULL
		&& is_builtin((const char **)mini->root_cmd->cmd))
	{
		if (!dup_fd(mini->root_cmd))
			mini->wstatus = exec_builtin(mini, mini->root_cmd);
	}
	else
	{
		env = cpy_lst_to_arr(mini->env);
		exec_commands(mini, temp_io, env);
		ft_delarray(env);
	}
	handle_temp_io(temp_io, 0);
	init_signals(&mini->sa);
	return (0);
}

static void	exec_commands(t_master *mini, int *temp_io, char **env)
{
	t_cmd	*cmd;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	cmd = mini->root_cmd;
	while (cmd)
	{
		while (cmd && cmd->io_error == true && !close_fd(cmd))
			cmd = cmd->next;
		if (!cmd || set_io(cmd, temp_io, true))
			return ;
		if (cmd->next && create_pipe(cmd))
			return ;
		if (set_io(cmd, temp_io, false))
			return ;
		mini->pid = fork();
		if (mini->pid == -1)
			mini_error(NULL, NULL, NULL, 0);
		else if (mini->pid == 0)
			exec_cmd(mini, cmd, env);
		cmd = cmd->next;
	}
	wait_loop(mini);
}

static int	exec_cmd(t_master *mini, t_cmd *cmd, char **env)
{
	if (!cmd->cmd)
		exit(0);
	if (is_builtin((const char **)cmd->cmd))
		exit(exec_builtin(mini, cmd));
	execve(cmd->path, cmd->cmd, env);
	if (errno == 126)
		exit(mini_error(cmd->cmd[0], NULL, NULL, 0));
	exit(mini_error(cmd->cmd[0], NULL, "command not found", 127));
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
		ret = mini_env(mini->env, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		ret = mini_exit(mini, &(cmd->cmd[1]));
	else if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		ret = mini_echo(&(cmd->cmd[1]));
	return (ret);
}

static int	heredoc_handler(t_list *env, t_cmd *cmd, t_master *mini)
{
	t_file	*temp;

	while (cmd)
	{
		temp = cmd->infile;
		while (temp)
		{
			if (temp->type == '+')
			{
				if (pipe(temp->herepipe) == -1)
					return (mini_error(NULL, NULL, NULL, 0));
				if (handle_heredoc(env, temp, temp->herepipe, mini) != 0)
					return (-2);
				if (cmd->io_error == true)
					close(temp->herepipe[0]);
			}
			temp = temp->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
