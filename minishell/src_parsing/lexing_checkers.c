/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:03:16 by vuljas            #+#    #+#             */
/*   Updated: 2025/03/12 16:03:20 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_expansions(t_master *mini, char *str);

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_cmd(t_token **tokens)
{
	t_token	*temp;
	int		res;

	res = 0;
	temp = *tokens;
	while (temp != NULL)
	{
		if (temp->type == CMD)
			res = 1;
		else if (temp->type == PIPE)
			res = 0;
		temp = temp->next;
	}
	return (res);
}

char	*get_operator_name(t_master *mini, int *i, int type)
{
	char	*res;

	if (mini->cleaned[*i] == ' ')
		(*i)++;
	res = extract_word(mini->cleaned, i);
	if (!res || type == HEREDOC)
		return (res);
	else
		return (check_expansions(mini, res));
}

static char	*check_expansions(t_master *mini, char *str)
{
	char	*res;

	if (!str)
		return (str);
	res = extract_quotes(str, mini, 0, 0);
	free(str);
	return (res);
}

void	check_envv_position(t_token **tokens, t_token **last_tok,
	char *envv_name)
{
	char	**buf_arr;
	int		i;

	buf_arr = ft_split(envv_name, ' ');
	free(envv_name);
	if (!buf_arr)
		return ;
	i = 0;
	while (buf_arr[i])
	{
		if (is_cmd(tokens) == 0)
			*last_tok = create_token(CMD, ft_strdup(buf_arr[i]));
		else
			*last_tok = create_token(ENVV, ft_strdup(buf_arr[i]));
		add_token(tokens, *last_tok);
		i++;
	}
	i = 0;
	while (buf_arr[i])
		free(buf_arr[i++]);
	free(buf_arr);
}
