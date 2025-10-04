/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_invalid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakurai <msakurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:08:18 by codespace         #+#    #+#             */
/*   Updated: 2025/10/04 15:58:11 by msakurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = 2147483647;
	line = get_next_line(fd);
	if (!line)
		printf("success: NULL when invalid\n");
	else
	{
		printf("error: not NULL when invalid\n");
		free(line);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
