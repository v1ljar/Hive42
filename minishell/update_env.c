/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:13:31 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/18 12:14:52 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static void	update_envlist(t_master *mini);

void	update_directories(t_master *mini)
{
	char	*temp_wd;

	temp_wd = getcwd(NULL, 0);
	if (!temp_wd)
		return ;
	if (ft_strcmp(mini->pwd, temp_wd))
	{
		free(mini->oldpwd);
		mini->oldpwd = mini->pwd;
		mini->pwd = getcwd(NULL, 0);
		update_envlist(mini);
	}
	free(temp_wd);
}

static void	update_envlist(t_master *mini)
{
	char	*temp_arg;
	t_list	*temp_lst;

	temp_lst = find_envp(mini->env, "OLDPWD");
	if (temp_lst)
	{
		temp_arg = ft_strjoin("OLDPWD=", mini->oldpwd);
		modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
	temp_lst = find_envp(mini->env, "PWD");
	if (temp_lst)
	{
		temp_arg = ft_strjoin("PWD=", mini->pwd);
		modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
}

void	update_last_argument(t_master *mini)
{
	int		i;
	char	*temp_arg;
	t_list	*temp_lst;
	t_cmd	*temp_cmd;

	temp_cmd = mini->root_cmd;
	if (!temp_cmd || count_commands(temp_cmd) > 1 || !temp_cmd->cmd)
		return ;
	i = 0;
	while (temp_cmd->cmd[i + 1])
		i++;
	temp_lst = find_envp(mini->env, "_");
	if (!ft_strcmp(temp_cmd->cmd[i], "$_"))
		return ;
	temp_arg = ft_strjoin("_=", temp_cmd->cmd[i]);
	if (!temp_arg)
		mini_error(NULL, NULL, "Out of memory", 1);
	else
	{
		modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
}

void	modify_envlist(t_list *env, t_list *tmp, char *str, bool replace)
{
	char	*new_str;

	new_str = NULL;
	if (replace)
	{
		ft_memset(tmp->content, 0, ft_strlen(tmp->content));
		free(tmp->content);
		new_str = ft_strdup(str);
		tmp->content = new_str;
	}
	else
	{
		new_str = ft_strdup(str);
		ft_lstadd_back(&env, ft_lstnew((void *)new_str));
	}
}
