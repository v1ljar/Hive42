/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:16:54 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/09 11:31:39 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	init_mini_struct(t_master *mini, char **env, int ac, char **av);
static int	process_input(t_master *mini);

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_master	mini;

	if (init_mini_struct(&mini, envp, argc, argv))
		return (mini_error(NULL, NULL, "Fatal error executing the program", 1));
	init_signals(&mini.sa);
	while (1)
	{
		rl_event_hook = (void *)signal_handler_rl;
		if (isatty(STDIN_FILENO))
			mini.input = readline("minishell> ");
		else
			mini.input = get_next_line(STDIN_FILENO);
		if (!mini.input || process_input(&mini) == -1)
			break ;
		free_cmds(&mini);
		if (mini.is_exit_set == true || errno == ENOMEM)
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
	ft_memset((void *)mini, 0, sizeof(t_master));
	if (!*env)
	{
		if (build_environment(mini))
			return (1);
	}
	else
	{
		if (copy_environment(mini, env))
		{
			clean_up(mini);
			return (1);
		}
	}
	return (0);
}

static int	process_input(t_master *mini)
{
	int	res;

	if (g_signal == SIGINT)
	{
		mini->wstatus = 130;
		g_signal = 0;
		return (0);
	}
	res = preprocessing_input(mini, 0);
	if (res == -1 || res == -2)
		return (res);
	lexer(mini, 0);
	if (mini->tokens == NULL)
		return (0);
	parser(mini);
	if (mini->root_cmd == NULL)
		return (0);
	if (update_last_argument(mini, 0))
		return (0);
	open_temp_io(mini->temp_io);
	if (mini_exec(mini) == 1)
		return (0);
	close_temp_io(mini->temp_io);
	init_signals(&mini->sa);
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
	if (mini->pwd)
		free(mini->pwd);
	if (mini->oldpwd)
		free(mini->oldpwd);
}
