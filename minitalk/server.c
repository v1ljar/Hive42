/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:45 by vuljas            #+#    #+#             */
/*   Updated: 2025/02/21 13:46:51 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *info, void *context);
static void handle_sig(int sig, unsigned int *pid);
static int 	len = 0;

int	main(int argc, char **argv)
{
	struct sigaction sa;

	if (argc != 1)
		return(ft_printf("Server program do NOT accept arguments!\n"));
	ft_printf("PID: %i\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static unsigned int 	v_pid;

	if (!v_pid)
		v_pid = -1;
	if (v_pid == -1)
		v_pid = info->si_pid;
	if (info->si_pid != v_pid)
		kill(info->si_pid, SIGKILL);
	if (v_pid == info->si_pid && sig == SIGUSR1)
		handle_sig(1, &v_pid);
	else if (v_pid == info->si_pid && sig == SIGUSR2)
		handle_sig(0, &v_pid);
	(void)context;
}

static void handle_sig(int sig, unsigned int *pid)
{
	static unsigned int		pos = 7;
	static unsigned char	c;
	static char				str[200000];

	c += (sig << pos);
	if (pos == 0)
	{
		str[len] = c;
		len++;
		if (pos == 0 && c == '\0')
		{
			ft_printf("%s", str);
			len = 0;
			*pid = -1;
		}
		pos = 7;
		c = 0;
	}

	else
		pos--;
}
