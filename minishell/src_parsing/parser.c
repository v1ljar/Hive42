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

/* Initialize t_token *input, to have pointer to tokens list to free them;
allocate and null-terminate memory for t_cmd *last_command and
t_master *parser_result */
static int	init_structs(t_token **input, t_cmd **last_cmd, t_master *mini);
/* Allocate memory for t_file *file, fills file values based on token values,
uses helper function to add file to respective list. */
static int	handle_redirection(t_master *mini, t_cmd **last_cmd);
/* Creates new t_cmp struct and adds it to the end of the commands list */
static void	handle_pipe(t_cmd **last_cmd, t_master *mini);
/* Creates or appends token value pointer to cmd pointer array respectively. */
static void	handle_args(t_cmd **last_cmd, t_master *mini);

void	parser(t_master *mini)
{
	t_cmd		*last_cmd;
	t_token		*input;

	if (init_structs(&input, &last_cmd, mini) != 0)
		return ;
	while (mini->tokens)
	{
		if (mini->tokens->type == INFILE || mini->tokens->type
			== HEREDOC || mini->tokens->type == OUTFILE
			|| mini->tokens->type == APPEND)
		{
			if (handle_redirection(mini, &last_cmd) == -1)
				break ;
		}
		else if (mini->tokens->type == PIPE)
			handle_pipe(&last_cmd, mini);
		else
			handle_args(&last_cmd, mini);
		if (mini->root_cmd == NULL)
			mini->root_cmd = last_cmd;
		mini->tokens = mini->tokens->next;
	}
	free_tokens_pointers(input, 0);
	mini->tokens = NULL;
}

static int	init_structs(t_token **input,
	t_cmd **last_cmd, t_master *mini)
{
	*input = mini->tokens;
	*last_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!*last_cmd)
		return (-1);
	(*last_cmd)->fdin = -1;
	(*last_cmd)->fdout = -1;
	return (0);
}

static int	handle_redirection(t_master *mini, t_cmd **last_cmd)
{
	static t_file	*file;

	if (!mini->tokens->value || mini->tokens->value[0] == '\0')
	{
		handle_redirection_error(mini, last_cmd);
		return (-1);
	}
	file = malloc(sizeof(t_file));
	if (!file)
		return (-1);
	if (mini->tokens->type == INFILE)
		file->type = '<';
	else if (mini->tokens->type == OUTFILE)
		file->type = '>';
	else if (mini->tokens->type == HEREDOC || mini->tokens->type == APPEND)
		file->type = '+';
	file->filename = mini->tokens->value;
	file->next = NULL;
	if (mini->tokens->type == INFILE || mini->tokens->type == HEREDOC)
		add_infile_to_list(last_cmd, file);
	else
		add_outfile_to_list(last_cmd, file);
	return (0);
}

static void	handle_pipe(t_cmd **last_cmd, t_master *mini)
{
	t_cmd	*new;
	t_cmd	*temp;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return ;
	new->fdin = -1;
	new->fdout = -1;
	temp = mini->root_cmd;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	*last_cmd = new;
}

static void	handle_args(t_cmd **last_cmd, t_master *mini)
{
	char	**new;
	int		i;

	if ((*last_cmd)->cmd == NULL)
	{
		new = (char **)ft_calloc(sizeof(char *) * 2, 1);
		if (!new)
			return ;
		*new = mini->tokens->value;
		(*last_cmd)->cmd = new;
		(*last_cmd)->path = find_path(mini->env, *new);
	}
	else
	{
		i = 0;
		while ((*last_cmd)->cmd[i] != NULL)
			i++;
		new = (char **)ft_calloc((sizeof(char *) * (i + 2)), 1);
		if (!new)
			return ;
		ft_memmove(new, (*last_cmd)->cmd, sizeof((*last_cmd)->cmd) * i);
		new[i] = mini->tokens->value;
		free((*last_cmd)->cmd);
		(*last_cmd)->cmd = new;
	}
}
