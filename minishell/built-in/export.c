/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:40:09 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:49:24 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	handle_args(t_list *env, char *arg, bool *export_error);
static int	print_export(t_list **env);
static void	sort_env(char **env_cpy);
static void	print(char *str);

int	mini_export(t_list *env, char **args)
{
	int		ret;
	bool	export_error;

	if (!args || *args == NULL)
	{
		if (print_export(&env))
			return (-1);
	}
	ret = 0;
	export_error = false;
	while (*args)
	{
		ret = handle_args(env, *args, &export_error);
		if (export_error || ret > 1)
			break ;
		args++;
	}
	return (ret);
}

static int	handle_args(t_list *env, char *arg, bool *export_error)
{
	int		i;
	char	temp_par[PATH_MAX];
	t_list	*temp_lst;

	i = 0;
	temp_lst = NULL;
	if (!ft_isalpha(arg[i]) && (arg[i] != '_'))
		return (mini_error("export", arg, "Not a valid identifier", 1));
	while (arg[i] && arg[i] != '=')
		i++;
	if (i >= PATH_MAX)
	{
		*export_error = true;
		return (mini_error("export", NULL, "Argument too long", 1));
	}
	ft_strlcpy(temp_par, arg, i + 1);
	temp_lst = find_envp(&env, temp_par);
	if (temp_lst)
		return (modify_envlist(env, temp_lst, arg, true));
	else
		return (modify_envlist(env, temp_lst, arg, false));
}

static int	print_export(t_list **env)
{
	char	**env_cpy;
	size_t	i;

	if (!*env)
		return (0);
	env_cpy = cpy_lst_to_arr(env);
	if (!env_cpy)
		return (mini_error(NULL, NULL, NULL, 0));
	sort_env(env_cpy);
	i = 0;
	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], "_=", 2))
			print(env_cpy[i]);
		i++;
	}
	ft_delarray(env_cpy);
	return (0);
}

static void	sort_env(char **env)
{
	char	**current;
	bool	is_swap;

	current = env;
	is_swap = false;
	while (current)
	{
		if (*(current + 1) == NULL)
		{
			if (is_swap == false)
				break ;
			current = env;
			is_swap = false;
		}
		if (ft_strcmp(*current, *(current + 1)) > 0)
		{
			is_swap = true;
			swap_ptrs(current, current + 1);
		}
		current++;
	}
}

static void	print(char *str)
{
	size_t	i;

	i = 0;
	write(STDOUT_FILENO, "declare -x ", 11);
	while (str[i] && str[i] != '=')
		write(STDOUT_FILENO, &(str[i++]), 1);
	if (str[i] == '=')
	{
		write(STDOUT_FILENO, &(str[i++]), 1);
		write(STDOUT_FILENO, "\"", 1);
		while (str[i])
			write(STDOUT_FILENO, &(str[i++]), 1);
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}
