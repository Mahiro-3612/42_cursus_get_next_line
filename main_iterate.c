/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:08:18 by codespace         #+#    #+#             */
/*   Updated: 2025/09/25 11:49:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("error: required number of argument is 1    @main");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
//	fd = 42;
	if (fd == -1)
	{
		printf("fatal error: open    @main\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(fd);
		printf("[%s]\n", line);
		if (!line)
		{
			printf("line is NULL    @main\n");
			break;
		}
		free(line);
	}
	close(fd);
	printf("end of main    @main\n");
	return (EXIT_SUCCESS);
}
