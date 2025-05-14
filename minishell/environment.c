/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:19:33 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:44:12 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_envv(t_list **env, const char *var)
{
	size_t	i;
	t_list	*temp;

	if (!var || !*env)
		return (NULL);
	i = 0;
	temp = *env;
	while (var[i])
		i++;
	while (temp)
	{
		if (!ft_strncmp((char *)temp->content, var, i))
		{
			if (*((char *)temp->content + i) == '=')
				return ((char *)(temp->content + i + 1));
			return (NULL);
		}
		temp = temp->next;
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
		if (!temp)
		{
			ft_lstclear(&env, del_content);
			return (NULL);
		}
		ft_lstadd_back(&env, ft_lstnew(temp));
		envp++;
	}
	return (env);
}

t_list	*find_envp(t_list **env, const char *parameter)
{
	size_t	i;
	t_list	*temp;

	if (!parameter || !env)
		return (NULL);
	i = 0;
	while (parameter[i])
		i++;
	temp = *env;
	while (temp)
	{
		if (!ft_strncmp((char *)temp->content, parameter, i))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	update_shlvl(t_list *env, int new_lvl)
{
	char	*temp_var;
	char	*new_variable;
	t_list	*temp_lst;

	temp_lst = find_envp(&env, "SHLVL");
	if (!temp_lst)
		return (-1);
	temp_var = find_envv(&env, "SHLVL");
	if (!temp_var)
		return (-1);
	new_lvl = ft_atoi(temp_var) + 1;
	temp_var = ft_itoa(new_lvl);
	if (!temp_var)
		return (mini_error(NULL, NULL, NULL, 0));
	new_variable = ft_strjoin("SHLVL=", temp_var);
	free(temp_var);
	if (!new_variable)
		return (mini_error(NULL, NULL, NULL, 0));
	new_lvl = modify_envlist(env, temp_lst, new_variable, true);
	free(new_variable);
	if (new_lvl)
		return (errno);
	return (0);
}

char	*find_path(t_list *env, char *cmd)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	paths = ft_split(find_envv(&env, "PATH"), ':');
	i = 0;
	while (*cmd && cmd[0] != '/' && cmd[0] != '.' && paths && paths[i])
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
	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	return (ft_strdup(""));
}
