#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
	char *str;
	char *str2;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file!\n");
	}
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	str2 = get_next_line(0);
	printf("%s", str2);
	return (0);
}
