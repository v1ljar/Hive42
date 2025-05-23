/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:48:32 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:57:04 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	unset_envp(t_list **env, t_list *to_unset);

int	mini_unset(t_master *mini, char **args)
{
	size_t	i;
	t_list	*to_unset;
	char	temp_par[PATH_MAX];

	if (!args)
		return (0);
	while (*args)
	{
		i = 0;
		while ((*args)[i] && (*args)[i] != '=')
			i++;
		ft_strlcpy(temp_par, *args, i + 1);
		if (!temp_par[0])
			return (0);
		to_unset = find_envp(&mini->env, temp_par);
		if (to_unset && ft_strncmp((char *)to_unset->content, "_=", 2))
			unset_envp(&mini->env, to_unset);
		args++;
	}
	return (0);
}

static void	unset_envp(t_list **env, t_list *to_unset)
{
	t_list	*next;
	t_list	*temp;

	next = to_unset->next;
	temp = *env;
	if (to_unset == *env)
		*env = (*env)->next;
	else
	{
		while (temp && temp->next != to_unset)
			temp = temp->next;
		temp->next = next;
	}
	ft_lstdelone(to_unset, &del_content);
}
