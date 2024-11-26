/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:30:39 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/26 17:52:27 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char*		result;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = ft_check_line(fd);
	if (result == NULL)
		return (NULL);
	else
		return (result);
}

int	main(void)
{
	int fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error!\n");
		return (-1);
	}
	else
		printf("%s\n", get_next_line(fd));
	close(fd);
	return (0);
}
