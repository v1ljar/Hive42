/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:40:27 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/02 14:06:14 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	is_alldigit(char *str)
{
	size_t	i;

	if (!str)
		return (false);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	mini_exit(t_master *mini, char **cmd)
{
	long long	n;

	n = 0;
	if (is_alldigit(cmd[0]) && cmd[1] != NULL)
		return (mini_error("exit", NULL, "too many arguments", 1));
	mini->is_exit_set = true;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!cmd[0])
		n = mini->wstatus;
	else if (!is_alldigit(cmd[0]))
		return (mini_error("exit", cmd[0], "numeric argument required", 2));
	else
	{
		n = ft_atoll(cmd[0]);
		if (n > INT_MAX || n < INT_MIN)
			return (mini_error("exit", cmd[0], "numeric argument required", 2));
	}
	return (n);
}
