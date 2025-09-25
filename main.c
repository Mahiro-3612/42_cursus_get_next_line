#include "get_next_line.h"

int	main(void)
{
	int fd = -100;
	// int fd = open("test.txt", O_RDONLY);
	// if (fd == -1)
	// 	return (1);
	// int count = 0;
	char *line = get_next_line(fd);
	while (line)
	{
		printf("[%s] \n", line);
		free(line);
		line = get_next_line(fd);
		// count++;
	}
	printf("[%s] \n", line);
	close(fd);
	return (0);
}