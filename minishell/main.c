/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:16:54 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/02 14:10:49 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_mini_struct(t_master *mini, char **env, int ac, char **av);
static int	process_input(t_master *mini);

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	static t_master	mini;

	init_signals(&mini.sa);
	if (init_mini_struct(&mini, envp, argc, argv))
		return (mini_error(NULL, NULL, "Fatal error executing the program", 1));
	while (1)
	{
		rl_event_hook = (void *)rl_signal_handler;
		if (isatty(STDIN_FILENO))
			mini.input = readline("minishell> ");
		else
			mini.input = get_next_line(STDIN_FILENO);
		if (!mini.input || process_input(&mini) == -1)
			break ;
		update_directories(&mini);
		free_cmds(&mini);
		if (mini.is_exit_set == true)
			break ;
	}
	if (mini.is_exit_set == false)
		ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	clean_up(&mini);
	return (mini.wstatus & 0xFF);
}

static int	init_mini_struct(t_master *mini, char **env, int ac, char **av)
{
	(void)av;
	(void)ac;
	mini->env = envcpy(env);
	if (!mini->env)
		return (mini_error(NULL, NULL, "Failed to build the environment", 1));
	mini->pwd = ft_strdup(getenv("PWD"));
	if (!mini->pwd)
		return (mini_error(NULL, NULL, "Failed to build the environment", 1));
	mini->oldpwd = ft_strdup(getenv("OLDPWD"));
	if (!mini->oldpwd)
		return (mini_error(NULL, NULL, "Failed to build the environment", 1));
	if (update_shlvl(mini->env))
		return (mini_error(NULL, NULL, "Failed to build the environment", 1));
	return (0);
}

static int	process_input(t_master *mini)
{
	int	res;

	res = preprocessing_input(mini, 0);
	if (res == -1 || res == -2)
		return (res);
	lexer(mini, 0);
	if (mini->tokens == NULL)
		return (0);
	parser(mini);
	if (mini->root_cmd == NULL)
		return (0);
	update_last_argument(mini);
	mini_exec(mini);
	return (mini->wstatus);
}

void	clean_up(t_master *mini)
{
	ft_lstclear(&mini->env, del_content);
	if (mini->root_cmd)
		free_cmds(mini);
	if (mini->input)
		free(mini->input);
	if (mini->cleaned)
		free(mini->cleaned);
	if (mini->tokens)
		free(mini->tokens);
	free(mini->pwd);
	free(mini->oldpwd);
}
