/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:19:33 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:34:18 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_list **env, char **cmd)
{
	t_list	*temp;

	if (!env)
		return (1);
	if (cmd[0])
		return (mini_error("env", NULL, "no arguments allowed", 127));
	temp = *env;
	while (temp)
	{
		if ((char *)temp->content && ft_strchr((char *)temp->content, '='))
			ft_putendl_fd((char *)temp->content, STDOUT_FILENO);
		temp = temp->next;
	}
	return (0);
}
