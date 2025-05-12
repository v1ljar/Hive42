/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:19:33 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 12:55:07 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_envv(t_list *env, const char *var)
{
	size_t	i;

	if (!var || !env)
		return (NULL);
	i = 0;
	while (var[i])
		i++;
	while (env)
	{
		if (!ft_strncmp((char *)env->content, var, i))
		{
			if (*((char *)env->content + i) == '=')
				return ((char *)(env->content + i + 1));
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

t_list	*envcpy(char **envp)
{
	t_list	*env;
	char	*temp;

	env = NULL;
	temp = NULL;
	while (*envp)
	{
		temp = ft_strdup(*envp);
		ft_lstadd_back(&env, ft_lstnew(temp));
		envp++;
	}
	return (env);
}

t_list	*find_envp(t_list *env, const char *parameter)
{
	size_t	i;

	if (!parameter || !env)
		return (NULL);
	i = 0;
	while (parameter[i])
		i++;
	while (env)
	{
		if (!ft_strncmp((char *)env->content, parameter, i))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	update_shlvl(t_list *env)
{
	char	*temp_var;
	char	*new_variable;
	int		new_lvl;
	t_list	*temp_lst;

	temp_lst = find_envp(env, "SHLVL");
	if (!temp_lst)
		return (-1);
	temp_var = find_envv(env, "SHLVL");
	if (!temp_var)
		return (-1);
	new_lvl = ft_atoi(temp_var) + 1;
	temp_var = ft_itoa(new_lvl);
	new_variable = ft_strjoin("SHLVL=", temp_var);
	if (!new_variable)
		return (-1);
	free(temp_var);
	modify_envlist(env, temp_lst, new_variable, true);
	free(new_variable);
	return (0);
}

char	*find_path(t_list *env, char *cmd)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	paths = ft_split(find_envv(env, "PATH"), ':');
	i = 0;
	while (*cmd && paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (!access(cmd_path, F_OK | X_OK))
		{
			ft_delarray(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_delarray(paths);
	return (ft_strdup(""));
}
