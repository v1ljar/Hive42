/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_token_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:03:30 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/09 13:52:35 by jpiensal         ###   ########.fr       */
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

int	check_tilde_add_to_buf(char *buf, char *str, int *i, t_master *mini)
{
	int		j;
	char	*temp;

	j = ft_strlen(buf);
	if ((*i == 0 && str[*i] == '~' && (str[*i + 1] == '/' || str[*i + 1] == ' '
				|| str[*i + 1] == '\0')) || (*i > 0 && str[*i - 1] == ' '
			&& str[*i] == '~' && (str[*i + 1] == '/' || str[*i + 1] == ' '
				|| str[*i + 1] == '\0')))
	{
		while (str[*i] != '~')
			(*i)++;
		(*i)++;
		temp = find_envv(&mini->env, "HOME");
		if (!temp)
			return (0);
		while (*temp)
			buf[j++] = *temp++;
	}
	else
		buf[j++] = str[(*i)++];
	return (j);
}
