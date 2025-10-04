#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error opening files");
		return (1);
	}
	while (1)
	{
		line1 = get_next_line(fd1);
		if (line1)
		{
			printf("%s", line1);
			free(line1);
		}
		line2 = get_next_line(fd2);
		if (line2)
		{
			printf("%s", line2);
			free(line2);
		}
		if (line1 == NULL && line2 == NULL)
			break ;
	}
	close(fd1);
	close(fd2);
	return (0);
}
