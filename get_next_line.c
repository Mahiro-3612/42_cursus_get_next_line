/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/21 13:47:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	char		*buf;
	ssize_t		bytes_read;
	char		*line;

	if (!next_buf)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buf);
			return (NULL);
		}
	}
	else
	{
		buf = ft_strdup(next_buf);
		free(next_buf);
	}
	line = get_until_newline(buf, &next_buf, BUFFER_SIZE);
	free(buf);
	if (!line)
	{
		free(next_buf);
		return (NULL);
	}
	return (line);
}
