#include "get_next_line.h"

int	main(void)
{
	// int	fd = 0;
	// int fd = open("normal_test.txt", O_RDONLY);
	// int fd = open("only_nl_test.txt", O_RDONLY);
	int fd = open("failing_test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	// int count = 0;
	char *line = get_next_line(fd);
	while (line)
	{
		printf("[%s] \n", line);
		free(line);
		line = get_next_line(fd);
		// count++;
	}
	if (line == NULL)
		printf("[NULL] \n");
	close(fd);
	return (0);
}
