/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:08:18 by codespace         #+#    #+#             */
/*   Updated: 2025/08/22 09:03:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	// int fd = open("test.txt", O_RDONLY);
	// if (fd == -1)
	// 	return (1);
	int	fd = 0;
	char *line = get_next_line(fd);
	while (line)
	{
		printf("[%s] \n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
