/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:46:50 by jpiensal          #+#    #+#             */
/*   Updated: 2025/01/22 11:17:28 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	finish_line(char *ret, char *buf)
{
	int32_t	i;
	int32_t	j;
	int32_t	line_end;

	if (!ret)
		return ;
	i = 0;
	j = 0;
	line_end = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	if (ret[i] == '\n')
	{
		line_end = i + 1;
		while (ret[++i])
			buf[j++] = ret[i];
		buf[j] = '\0';
		ret[line_end] = '\0';
	}
	else
		buf[j] = '\0';
}

static int	find_next_line(const char *str)
{
	int32_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		else
			i++;
	}
	return (0);
}

static int	check_read(int32_t read, char *line)
{
	if (read < 0)
	{
		if (line)
			free(line);
		line = NULL;
		return (0);
	}
	else if (read == 0)
		return (0);
	else
		return (1);
}

static char	*read_line(int fd)
{
	int32_t		bytes_read;
	static char	buf[BUFFER_SIZE + 1];
	char		*cur_line;

	bytes_read = 0;
	cur_line = gnl_strdup(buf);
	while (!find_next_line(cur_line))
	{
		bytes_read = read (fd, &buf, BUFFER_SIZE);
		if (!check_read(bytes_read, cur_line))
			break ;
		buf[bytes_read] = '\0';
		cur_line = gnl_strjoin_n_free(cur_line, buf);
		if (!cur_line)
			return (NULL);
	}
	finish_line(cur_line, buf);
	if (cur_line && cur_line[0] == '\0')
	{
		free(cur_line);
		return (NULL);
	}
	return (cur_line);
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = read_line(fd);
	if (!line)
		return (NULL);
	return (line);
}
