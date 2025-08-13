/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/13 16:28:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	ssize_t	read_bytes;
	ssize_t read_bytes_next;
	char	*buf;
	char	*next_buf;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_bytes = read(fd, buf, BUFFER_SIZE);
	if (read_bytes <= 0)
	{
		free(buf);
		return (NULL);
	}
	else
	{
		next_buf = ft_calloc(1, sizeof(char));
		read_bytes_next = read(fd, next_buf, 1);
		if (read_bytes_next > 0)
			buf[read_bytes] = '\0';
		free(next_buf);
		return (buf);
	}
}
