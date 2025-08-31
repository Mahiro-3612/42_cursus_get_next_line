/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:08:18 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 09:00:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	// int	fd = 0;
	int fd = open("tests/normal_test.txt", O_RDONLY);
	// int fd = open("tests/only_nl_test.txt", O_RDONLY);
	// int fd = open("tests/1char_test.txt", O_RDONLY);
	// int fd = open("tests/empty.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	int count = 0;
	char *line = get_next_line(fd);
	while (line && count < 20)
	{
		printf("[%s] \n", line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	if (line == NULL)
		printf("[NULL] \n");
	close(fd);
	return (0);
}
