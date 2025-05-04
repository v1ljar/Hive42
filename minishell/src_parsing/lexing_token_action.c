/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_token_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:03:30 by vuljas            #+#    #+#             */
/*   Updated: 2025/03/12 16:03:34 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

void	add_token(t_token **tokens_list, t_token *new)
{
	t_token	*temp;

	if (!*tokens_list)
	{
		*tokens_list = new;
		return ;
	}
	temp = *tokens_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
