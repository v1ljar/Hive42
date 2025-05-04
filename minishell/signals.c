/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:09:54 by vuljas            #+#    #+#             */
/*   Updated: 2025/04/04 11:28:48 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal);

void	init_signals(struct sigaction *sa)
{
	sa->sa_handler = signal_handler;
	sa->sa_flags = SA_RESTART;
	sigaction(SIGQUIT, sa, NULL);
	sigaction(SIGINT, sa, NULL);
	sigemptyset(&sa->sa_mask);
	g_signal = 0;
	rl_catch_signals = 0;
}

static void	signal_handler(int signal)
{
	if (g_signal == 0 && signal == SIGINT)
		g_signal = SIGINT;
	if (g_signal == 0 && signal == SIGQUIT)
		g_signal = SIGQUIT;
}

void	rl_signal_handler(void)
{
	if (g_signal == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		g_signal = 0;
	}
}

void	exec_signals_handler(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		write(STDOUT_FILENO, "^C", 2);
	}
	else if (g_signal == SIGQUIT)
	{
		g_signal = 0;
	}
}
