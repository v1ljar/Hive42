/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:54:09 by vuljas            #+#    #+#             */
/*   Updated: 2025/04/18 01:54:09 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_open_pipe(char *temp, int i, t_master *mini, int j)
{
	while (temp[i] != '\0')
	{
		if (temp[i] == '|')
		{
			j = i + 1;
			while (temp[j] != '\0')
			{
				if (temp[j] == ' ' || temp[j] == '\n'
					|| temp[j] == '\t' || temp[j] == '\r')
					j++;
				else if (temp[j] == '|')
				{
					mini->wstatus = 2;
					return (0);
				}
				else
					break ;
			}
		}
		i++;
	}
	if (i > 1 && temp[i - 1] == '|')
		return (1);
	return (0);
}

int	free_n_continue(char **str, t_master *mini)
{
	free(*str);
	mini->wstatus = 130;
	*str = NULL;
	g_signal = 0;
	return (-2);
}
