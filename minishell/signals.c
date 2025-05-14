/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:09:54 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/08 14:34:32 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal);

void	init_signals(struct sigaction *sa)
{
	sa->sa_handler = signal_handler;
	sa->sa_flags = 0;
	sigaction(SIGQUIT, sa, NULL);
	sigaction(SIGINT, sa, NULL);
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
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

void	signal_handler_rl(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		write(STDOUT_FILENO, "^C", 3);
	}
	if (g_signal == SIGQUIT)
		g_signal = 0;
}

int	is_heredoc_signal(t_master *mini, int *fd, char *line)
{
	if (g_signal == SIGINT)
	{
		close(fd[0]);
		close(fd[1]);
		if (line)
			free(line);
		mini->wstatus = 130;
		g_signal = 0;
		return (-2);
	}
	return (0);
}
