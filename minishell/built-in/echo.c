/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:31:15 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/02 12:17:39 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static bool	is_new_line(char **cmd, int *i)
{
	bool	ret;

	ret = true;
	while (cmd[*i])
	{
		if (!ft_strncmp(cmd[*i], "-n", 2)
			&& (ft_strspn(&cmd[*i][1], "n") == ft_strlen(&cmd[*i][1])))
		{
			*i += 1;
			ret = false;
		}
		else
			break ;
	}
	return (ret);
}

static void	print(const char *str, bool is_last)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(STDOUT_FILENO, &str[i++], 1);
	if (!is_last)
		write(STDOUT_FILENO, " ", 1);
}

int	mini_echo(char **cmd)
{
	int		i;
	bool	print_n;

	i = 0;
	print_n = is_new_line(cmd, &i);
	while (cmd[i])
	{
		if (cmd[i + 1] == NULL)
			print(cmd[i], true);
		else
			print(cmd[i], false);
		i++;
	}
	if (print_n == true)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
