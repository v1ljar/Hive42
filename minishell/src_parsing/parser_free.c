/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:53:38 by vuljas            #+#    #+#             */
/*   Updated: 2025/03/12 13:53:43 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_pointers(t_token *tokens_list, int err)
{
	t_token	*temp;

	while (tokens_list != NULL)
	{
		temp = tokens_list->next;
		if ((err == 1 || tokens_list->type == PIPE) && tokens_list->value)
		{
			free(tokens_list->value);
			tokens_list->value = NULL;
		}
		if (err == 0)
			free(tokens_list);
		tokens_list = temp;
	}
}

void	free_cmds(t_master *mini)
{
	t_cmd	*temp;

	if (!mini)
		return ;
	while (mini->root_cmd)
	{
		temp = mini->root_cmd->next;
		if (mini->root_cmd->cmd)
			ft_delarray(mini->root_cmd->cmd);
		if (mini->root_cmd->infile)
			iterate_list_free(mini->root_cmd, 1);
		if (mini->root_cmd->outfile)
			iterate_list_free(mini->root_cmd, 0);
		if (mini->root_cmd->path)
			free(mini->root_cmd->path);
		free(mini->root_cmd);
		mini->root_cmd = temp;
	}
	mini->root_cmd = NULL;
	free(mini->cleaned);
	mini->cleaned = NULL;
}

void	iterate_list_free(t_cmd *temp, int id)
{
	t_file	*iter_temp;

	if (id == 1)
	{
		while (temp->infile)
		{
			iter_temp = temp->infile;
			temp->infile = temp->infile->next;
			if (iter_temp->filename)
				free(iter_temp->filename);
			free(iter_temp);
		}
	}
	else
	{
		while (temp->outfile)
		{
			iter_temp = temp->outfile;
			temp->outfile = temp->outfile->next;
			if (iter_temp->filename)
				free(iter_temp->filename);
			free(iter_temp);
		}
	}
}
