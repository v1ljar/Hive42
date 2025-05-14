/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:38:09 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:54:08 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	update_wd(t_master *mini);
static int	update_envlist(t_master *mini);

int	mini_cd(t_master *mini, char **cmd)
{
	struct stat	info;
	char		*temp;

	if (!cmd[0])
		temp = find_envv(&mini->env, "HOME");
	else if (!ft_strncmp(cmd[0], "-", 2))
		temp = mini->oldpwd;
	else
		temp = cmd[0];
	if (cmd[0] && cmd[1])
		return (mini_error("cd", NULL, "Too many arguments", 1));
	else if (stat(temp, &info))
		return (mini_error("cd", cmd[0], NULL, 0));
	else if (!S_ISDIR(info.st_mode))
		return (mini_error("cd", cmd[0], "Not a directory", 1));
	else if (!(info.st_mode & S_IXUSR))
		return (mini_error("cd", cmd[0], "Permission denied", 1));
	if (chdir(temp) == -1)
		return (mini_error("cd", temp, NULL, 0));
	if (update_wd(mini))
		return (errno);
	return (0);
}

static int	update_wd(t_master *mini)
{
	char	*temp_wd;

	temp_wd = getcwd(NULL, 0);
	if (!temp_wd)
		return (mini_error("cd", NULL, NULL, 0));
	if (ft_strcmp(mini->pwd, temp_wd))
	{
		free(mini->oldpwd);
		mini->oldpwd = mini->pwd;
		mini->pwd = getcwd(NULL, 0);
		if (!mini->pwd)
		{
			free(temp_wd);
			return (mini_error(NULL, NULL, NULL, 0));
		}
		if (update_envlist(mini))
		{
			free(temp_wd);
			return (errno);
		}
	}
	free(temp_wd);
	return (0);
}

static int	update_envlist(t_master *mini)
{
	char	*temp_arg;
	t_list	*temp_lst;

	temp_lst = find_envp(&mini->env, "OLDPWD");
	if (temp_lst)
	{
		temp_arg = ft_strjoin("OLDPWD=", mini->oldpwd);
		if (!temp_arg)
			return (mini_error(NULL, NULL, NULL, 0));
		modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
	temp_lst = find_envp(&mini->env, "PWD");
	if (temp_lst)
	{
		temp_arg = ft_strjoin("PWD=", mini->pwd);
		if (!temp_arg)
			return (mini_error(NULL, NULL, NULL, 0));
		modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
	return (0);
}
