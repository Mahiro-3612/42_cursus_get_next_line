#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line.h"

int main(int argc, char **argv)
{
	char *line;
	int	fd;

	(void)argc;
	fd = open(argv[1], O_RDONLY);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("\n\nend of gnl\n");
			break;
		}
		printf("line:[%s]\n", line);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
