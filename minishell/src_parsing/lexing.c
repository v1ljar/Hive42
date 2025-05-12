/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:53:38 by vuljas            #+#    #+#             */
/*   Updated: 2025/04/04 13:04:02 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* handle_envv handles envv if not in quotes, according the ENVV name,
expand the value and create token accordingly */
static void	handle_envv(t_master *mini, int *i, t_token **tokens,
				t_token **last_tok);
/* handle_operator processes the right operator value (name after the
operator) and type and creates token accordingly */
static void	handle_operator(char *str, int *i, t_token **last_tok,
				t_master *mini);
/* handle_word gets the word from the string and adds to token accordingly,
based on the position of the word */
static void	handle_word(char *str, int *i, t_master *mini,
				t_token **last_tok);

void	lexer(t_master *mini, int i)
{
	t_token	*last_token;
	char	*str;

	last_token = NULL;
	if (!last_token && (mini->cleaned && mini->cleaned[0] == '|'))
	{
		mini->wstatus = 2;
		mini_error(NULL, NULL, "syntax error near unexpected token `|'", 2);
		return ;
	}
	str = mini->cleaned;
	while (i <= (int)ft_strlen(str) && str[i] != '\0')
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'
				|| str[i + 1] == '_'))
			handle_envv(mini, &i, &mini->tokens, &last_token);
		else if (is_operator(str[i]))
			handle_operator(str, &i, &last_token, mini);
		else if (str[i] == ' ')
			i++;
		else
			handle_word(str, &i, mini, &last_token);
	}
	free(mini->cleaned);
	mini->cleaned = NULL;
}

void	handle_envv(t_master *mini, int *i, t_token **tokens,
			t_token **last_tok)
{
	char	*envv_name;
	char	*str;

	str = mini->cleaned;
	if ((*last_tok == NULL || (*last_tok)->type == PIPE) && str[*i + 1] == ' ')
	{
		*last_tok = create_token(CMD, ft_strdup("$"));
		add_token(tokens, *last_tok);
		(*i)++;
		return ;
	}
	else if (str[*i + 1] == ' ' || str[*i + 1] == '"' || str[*i + 1] == '\''
		|| str[*i + 1] == '\0')
		(*i)++;
	else
	{
		envv_name = expand_envv(mini, str, i, 0);
		if (envv_name)
			check_envv_position(tokens, last_tok, envv_name);
		else
			(*i)++;
	}
	return ;
}

static void	handle_operator(char *str, int *i, t_token **last_tok,
				t_master *mini)
{
	char			operator[3];
	t_token_type	type;

	ft_bzero(operator, 3);
	operator[0] = str[*i];
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>'
			&& str[*i + 1] == '>'))
		operator[1] = str[((*i)++) + 1];
	(*i)++;
	if (ft_strcmp(operator, "<") == 0)
		type = INFILE;
	else if (ft_strcmp(operator, ">") == 0)
		type = OUTFILE;
	else if (ft_strcmp(operator, "|") == 0)
		type = PIPE;
	else if (ft_strcmp(operator, "<<") == 0)
		type = HEREDOC;
	else
		type = APPEND;
	if (type == PIPE)
		*last_tok = create_token(type, ft_strdup("|"));
	else
		*last_tok = create_token(type, get_operator_name(mini, i, type));
	add_token(&mini->tokens, *last_tok);
}

void	handle_word(char *str, int *i, t_master *mini, t_token **last_tok)
{
	char	*word;

	word = extract_word(str, i);
	if (!word)
		return ;
	if (*last_tok == NULL || (*last_tok != NULL
			&& is_cmd(&mini->tokens) == 0))
		*last_tok = create_token(CMD, extract_quotes(word, mini, 0, 0));
	else
		*last_tok = create_token(ARG, extract_quotes(word, mini, 0, 0));
	free(word);
	add_token(&mini->tokens, *last_tok);
}
