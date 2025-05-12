/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:19:33 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/02 14:04:12 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_env(t_list *env, char **cmd)
{
	if (!env)
		return (1);
	if (cmd[0])
		return (mini_error("env", NULL, "no arguments allowed", 127));
	while (env)
	{
		if ((char *)env->content && ft_strchr((char *)env->content, '='))
			ft_putendl_fd((char *)env->content, STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}
