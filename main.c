/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakurai <msakurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:08:18 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 13:53:02 by msakurai         ###   ########.fr       */
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
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}




// #include "get_next_line.h"
//
// int	main(void)
// {
// 	// int	fd = 0;
// 	// int fd = open("normal_test.txt", O_RDONLY);
// 	// int fd = open("only_nl_test.txt", O_RDONLY);
// 	int fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	// int count = 0;
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("[%s] \n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 		// count++;
// 	}
// 	if (line == NULL)
// 		printf("[NULL] \n");
// 	close(fd);
// 	return (0);
// }
