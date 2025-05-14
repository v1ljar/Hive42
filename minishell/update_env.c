/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:13:31 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:44:56 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	update_last_argument(t_master *mini, int i)
{
	char	*temp_arg;
	t_list	*temp_lst;
	t_cmd	*temp_cmd;

	temp_cmd = mini->root_cmd;
	if (!temp_cmd || count_commands(temp_cmd) > 1 || !temp_cmd->cmd)
		return (0);
	while (temp_cmd->cmd[i + 1])
		i++;
	temp_lst = find_envp(&mini->env, "_");
	if (!ft_strcmp(temp_cmd->cmd[i], "$_"))
		return (0);
	temp_arg = ft_strjoin("_=", temp_cmd->cmd[i]);
	if (!temp_arg)
		return (mini_error(NULL, NULL, NULL, 0));
	else
	{
		i = modify_envlist(mini->env, temp_lst, temp_arg, true);
		free(temp_arg);
	}
	if (i)
		return (i);
	return (0);
}

int	modify_envlist(t_list *env, t_list *tmp, char *str, bool replace)
{
	char	*new_str;

	new_str = str;
	new_str = NULL;
	if (replace)
	{
		ft_memset(tmp->content, 0, ft_strlen(tmp->content));
		new_str = ft_strdup(str);
		if (!new_str)
			return (mini_error(NULL, NULL, NULL, 0));
		free(tmp->content);
		tmp->content = new_str;
	}
	else
	{
		new_str = ft_strdup(str);
		if (!new_str)
			return (mini_error(NULL, NULL, NULL, 0));
		ft_lstadd_back(&env, ft_lstnew((void *)new_str));
	}
	return (0);
}

void	free_env_strings(char *shlvl, char *last_arg, char *pwd)
{
	free(shlvl);
	free(last_arg);
	free(pwd);
}
