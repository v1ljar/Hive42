/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:53:38 by vuljas            #+#    #+#             */
/*   Updated: 2025/04/04 12:44:30 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "minishell.h"

void	add_infile_to_list(t_cmd **last_cmd, t_file *file)
{
	t_file	*temp;

	if ((*last_cmd)->infile == NULL)
		(*last_cmd)->infile = file;
	else
	{
		temp = (*last_cmd)->infile;
		while (temp->next)
			temp = temp->next;
		temp->next = file;
	}
}

void	add_outfile_to_list(t_cmd **last_cmd, t_file *file)
{
	t_file	*temp;

	if ((*last_cmd)->outfile == NULL)
		(*last_cmd)->outfile = file;
	else
	{
		temp = (*last_cmd)->outfile;
		while (temp->next)
			temp = temp->next;
		temp->next = file;
	}
}

void	handle_redirection_error(t_master *mini, t_cmd **last_cmd)
{
	if (!mini->tokens->value || mini->tokens->value[0] == '\0')
	{
		if (mini->tokens->type == INFILE)
			mini_error(NULL, NULL, "syntax error near token `<'", 2);
		else if (mini->tokens->type == OUTFILE)
			mini_error(NULL, NULL, "syntax error near token `>'", 2);
		else if (mini->tokens->type == HEREDOC)
			mini_error(NULL, NULL, "syntax error near token `<<'", 2);
		else
			mini_error(NULL, NULL, "syntax error near token `>>'", 2);
		mini->wstatus = 2;
		free_tokens_pointers(mini->tokens, 1);
		if (mini->root_cmd)
			free_cmds(mini);
		else
		{
			free(*last_cmd);
			*last_cmd = NULL;
		}
	}
}
