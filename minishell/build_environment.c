/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:16:54 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/09 14:07:20 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_content(t_list **env, char *shlvl, char *last_arg, char *pwd)
{
	char	*pwd_env;

	pwd_env = ft_strjoin("PWD=", pwd);
	if (!pwd_env)
	{
		free_env_strings(shlvl, last_arg, pwd);
		return (-1);
	}
	free(pwd);
	ft_lstadd_back(env, ft_lstnew((void *)pwd_env));
	ft_lstadd_back(env, ft_lstnew((void *)shlvl));
	ft_lstadd_back(env, ft_lstnew((void *)last_arg));
	if (!env)
	{
		free_env_strings(shlvl, last_arg, pwd_env);
		return (-1);
	}
	return (0);
}

static t_list	*create_env(void)
{
	t_list	*env;
	char	*shlvl;
	char	*last_arg;
	char	*pwd;

	shlvl = ft_strdup("SHLVL=1");
	last_arg = ft_strdup("_=''");
	pwd = getcwd(NULL, 0);
	if (!shlvl || !last_arg || !pwd)
	{
		free_env_strings(shlvl, last_arg, pwd);
		return (NULL);
	}
	env = NULL;
	if (add_content(&env, shlvl, last_arg, pwd))
		return (NULL);
	return (env);
}

static int	create_mini(t_master *mini)
{
	mini->pwd = getcwd(NULL, 0);
	if (!mini->pwd)
		return (-1);
	mini->oldpwd = ft_strdup(mini->pwd);
	if (!mini->oldpwd)
	{
		free(mini->pwd);
		return (-1);
	}
	return (0);
}

int	build_environment(t_master *mini)
{
	mini->env = create_env();
	if (!mini->env)
		return (-1);
	if (create_mini(mini))
		return (-1);
	return (0);
}

int	copy_environment(t_master *mini, char **env)
{
	mini->env = envcpy(env);
	if (!mini->env)
		return (-1);
	if (getenv("PWD"))
	{
		mini->pwd = ft_strdup(getenv("PWD"));
		if (!mini->pwd)
			return (-1);
	}
	if (getenv("OLDPWD"))
		mini->oldpwd = ft_strdup(getenv("OLDPWD"));
	else if (mini->pwd)
		mini->oldpwd = ft_strdup(mini->pwd);
	if (mini->pwd && !mini->oldpwd)
		return (-1);
	if (update_shlvl(mini->env, 0) > 0)
		return (-1);
	return (0);
}
