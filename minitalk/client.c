/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:46:15 by vuljas            #+#    #+#             */
/*   Updated: 2025/02/21 13:46:19 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

static void	ft_send_bits(int pid, char *str);

int	main(int argc, char **argv)
{
	int pid;

	if (argc != 3)
		return (ft_printf("Invalid amount of arguments!\n"));
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Invalid PID!\n"));
	ft_send_bits(pid, argv[2]);
	ft_printf("Signal sent to %i.\n", pid);
	return (0);
}

static void	ft_send_bits(int pid, char *str)
{
	int				pos;
	unsigned char	c;

	while (*str)
	{
		pos = 8;
		c = *str++;
		while (pos--)
		{
			if (c >> pos & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(250);
		}
	}
	pos = 8;
	while (pos--)
	{
		kill(pid, SIGUSR2);
		usleep(250);
	}
}
