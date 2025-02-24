#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*result = NULL;
	char		temp[2000];
	int			bytes_read;
	static char	*buffer;
	static int	len = 0;
	int			i;

	bytes_read = 0;
	if (!buffer && len == 0)
	{
		if ((bytes_read = (int)read(fd, temp, 2000)) < 0)
			return NULL;
		temp[bytes_read] = '\0';
		buffer = malloc(sizeof(char) * (long unsigned int)bytes_read + 1);
		if (!buffer)
			return NULL;
		i = 0;
		while (temp[i] != '\0')
		{
			buffer[i] = temp[i];
			i++;
		}
		buffer[i] = '\0';
	}
	if (buffer == NULL)
		return NULL;
	if (*buffer)
	{
		i = 0;
		while (buffer[len + i] && buffer[(int)len + i] != '\n')
			i++;
		result = malloc(sizeof(char) * ((long unsigned int)i + 1));
		if (!result)
			return (NULL);
		i = 0;
		while (buffer[len + i] && buffer[(int)len + i] != '\n')
		{
			result[i] = buffer[i + (int)len];
			i++;
		}
		if (buffer[(int)len + i] == '\n')
			result[i++] = '\n';
		if (buffer[(int)len + i] == '\0')
		{
			free(buffer);
			buffer = NULL;
		}
		result[i] = '\0';
		len += i;
		return result;
	}
	else
		return NULL;
}

int	main(void)
{
	int	fd = 0;
	char *str;

	str = NULL;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}