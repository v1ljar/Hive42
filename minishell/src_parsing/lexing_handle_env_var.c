/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_handle_env_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:04:10 by vuljas            #+#    #+#             */
/*   Updated: 2025/05/09 13:53:16 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	increment_len_n_check_qm(char *str, int start, int *len);

char	*expand_env_var(t_master *mini, char *str, int *i, int len)
{
	char	*envv_name;
	char	*res;
	int		start;

	start = *i + 1;
	if (!ft_isalnum(str[start]) && str[start] != '_' && str[start] != '?')
		return (NULL);
	while (str[start + len] && (ft_isalnum(str[start + len])
			|| (str[start + len] == '_' || str[start + len] == '?')))
		if (increment_len_n_check_qm(str, start, &len) == -1)
			break ;
	envv_name = ft_substr(str, start, len);
	*i += len + 1;
	if (envv_name && !ft_strncmp(envv_name, "?", 2))
		res = ft_itoa(mini->wstatus);
	else
		res = ft_strdup(find_envv(&mini->env, envv_name));
	free(envv_name);
	if (!res && (str[*i] == ' ' || str[*i] == '\0'))
		return (NULL);
	else if (res && (str[*i] == ' ' || str[*i] == '\0'))
		return (res);
	else
		return (extract_full_variable(str, i, res, mini));
}

char	*extract_full_variable(char *str, int *i, char *envv_name,
			t_master *mini)
{
	char	*res;
	char	*buf;
	char	*save;
	char	*addition;

	addition = extract_word(str, i);
	if (!addition)
		return (envv_name);
	save = mini->cleaned;
	mini->cleaned = addition;
	buf = process_word(addition, mini, 0, 0);
	free(addition);
	mini->cleaned = save;
	if (!buf)
		return (envv_name);
	if (envv_name)
		res = ft_strjoin(envv_name, buf);
	else
		res = ft_strdup(buf);
	free(envv_name);
	free(buf);
	if (!res)
		return (NULL);
	return (res);
}

void	extract_envv_quotes(t_master *mini, char **buf, int *i, int *j)
{
	char	*value;
	char	*env_v;
	int		start;
	int		len;

	value = mini->cleaned;
	start = *i + 1;
	len = 0;
	if (!ft_isalnum(value[start]) && value[start] != '_' && value[start] != '?')
	{
		(*i)++;
		return ;
	}
	while (((value[start + len] != '\0' && ft_isalnum(value[start + len]))
			|| (value[start + len] == '_' || value[start + len] == '?')))
		len++;
	value = ft_substr(mini->cleaned, start, len);
	*i += len + 1;
	if (value && !ft_strncmp(value, "?", 2))
		env_v = ft_itoa(mini->wstatus);
	else
		env_v = ft_strdup(find_envv(&mini->env, value));
	free(value);
	if (env_v)
		envv_to_str(buf, env_v, j);
}

void	envv_to_str(char **buf, char *env_v, int *j)
{
	int	i;

	i = 0;
	while (env_v[i] != '\0')
	{
		(*buf)[(*j)++] = env_v[i++];
	}
	free(env_v);
}

static int	increment_len_n_check_qm(char *str, int start, int *len)
{
	(*len)++;
	if (str[start + *len - 1] == '?')
		return (-1);
	return (0);
}
