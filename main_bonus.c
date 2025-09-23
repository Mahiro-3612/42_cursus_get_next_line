
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd0;
	int		fd1;
	char	*line0;
	char	*line1;

	if (argc != 3)
	{
		printf("error: required number of argument is 2    @main_bonus");
		return (EXIT_FAILURE);
	}
	fd0 = open(argv[1], O_RDONLY);
	fd1 = open(argv[2], O_RDONLY);
//	fd = 42;
	if (fd0 == -1 || fd1 == -1)
	{
		printf("fatal error: open    @main_bonus\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line0 = get_next_line(fd0);
		line1 = get_next_line(fd1);
		printf("[%s]\n", line0);
		printf("[%s]\n", line1);
		if (!line0)
		{
			printf("line is NULL    @main_bonus\n");
			free(line1);
			break;
		}
		if (!line1)
		{
			printf("line is NULL    @main_bonus\n");
			free(line0);
			break;
		}
		free(line0);
		free(line1);
	}
	close(fd0);
	close(fd1);
	printf("end of main    @main_bonus\n");
	return (EXIT_SUCCESS);
}
