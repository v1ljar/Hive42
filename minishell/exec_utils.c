/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:42:53 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/29 12:02:51 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	count_commands(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	**cpy_lst_to_arr(t_list *lst)
{
	size_t	len;
	size_t	i;
	char	**arr;

	if (!lst)
		return (NULL);
	len = ft_lstsize(lst);
	arr = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		arr[i++] = ft_strdup((char *)lst->content);
		lst = lst->next;
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

void	wait_loop(t_master *mini)
{
	int	pid;
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
			write(STDOUT_FILENO, "\n", 1);
			status = WTERMSIG(status) + 128;
			if (pid == mini->pid)
				mini->wstatus = status;
			return ;
		}
		if (pid == mini->pid)
			mini->wstatus = status;
		if (pid == -1)
			break ;
	}
}

int	is_heredoc_signal(t_master *mini, int *fd, char *line)
{
	if (g_signal == SIGINT)
	{
		close(fd[0]);
		close(fd[1]);
		if (line)
			free(line);
		mini->wstatus = 130;
		g_signal = 0;
		return (-2);
	}
	return (0);
}
