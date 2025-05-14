/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:42:53 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 13:51:22 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**cpy_lst_to_arr(t_list **lst)
{
	size_t	len;
	size_t	i;
	char	**arr;
	t_list	*temp;

	if (!lst)
		return (NULL);
	len = ft_lstsize(*lst);
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	temp = *lst;
	while (temp)
	{
		arr[i++] = ft_strdup((char *)temp->content);
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	swap_ptrs(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	wait_loop(t_master *mini, bool flag, int pid)
{
	int	status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		pid = wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status) + 128;
			if (!flag && status == 131)
				ft_putendl_fd("Quit (core dumped)", 2);
			else if (!flag && status == 130)
				ft_putendl_fd("", 2);
			flag = true;
		}
		if (status == ENOMEM)
			mini->is_exit_set = true;
		if (pid == mini->pid)
			mini->wstatus = status;
		if (pid == -1)
			break ;
	}
}

int	print_warning(char *limiter, t_master *mini, int *fd, bool flag)
{
	char	*temp;

	if (flag)
	{
		ft_putstr_fd("Minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted '", 2);
		ft_putstr_fd(limiter, 2);
		ft_putendl_fd("')", 2);
	}
	else
	{
		temp = ft_itoa(mini->wstatus);
		if (!temp)
			return (mini_error(NULL, NULL, NULL, 0));
		write(fd[1], temp, ft_strlen(temp));
		free(temp);
	}
	return (0);
}
