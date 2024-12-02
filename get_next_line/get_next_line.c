/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:30:39 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/30 10:06:14 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

char	*ft_extract_line(char **buffer)
{
	char	*new_buffer;
	char	*new_line;
	char	*line;

	if (*buffer[0] == '\0')
		return (NULL);
	new_line = ft_strchr(*buffer, '\n');
	if (new_line)
	{
		line = ft_substr(*buffer, 0, (new_line - *buffer) + 1);
		new_buffer = ft_strdup(new_line + 1);
	}
	else
	{
		line = ft_strdup(*buffer);
		new_buffer = ft_strdup("");
	}
	free(*buffer);
	*buffer = ft_strdup(new_buffer);
	free(new_buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		temp[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	return (ft_extract_line(&buffer));
}

int	main(void)
{
	int	fd;

	char *str;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error!\n");
		return (-1);
	}

	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}
