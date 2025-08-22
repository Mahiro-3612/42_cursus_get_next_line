/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/22 09:24:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	char		*buf;
	ssize_t		bytes_read;
	char		*line;
	ssize_t		i;
	ssize_t		size;

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
		next_buf = NULL;
		if (!buf)
			return (NULL);
	}
	i = 0;
	size = ft_strlen(buf);
	if (size == 0)
	{
		free(buf);
		return (NULL);
	}
	while (buf[i] != '\n' && buf[i])
	{
		if (i == size - 1)
		{
			next_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			if (!next_buf)
				break ;
			bytes_read = read(fd, next_buf, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				free(buf);
				free(next_buf);
				next_buf = NULL;
				return (NULL);
			}
			else if (bytes_read == 0)
				{
					free(next_buf);
					next_buf = NULL;
					break ;
				}
			buf = ft_strjoin_with_free(buf, &next_buf);
			size += bytes_read;
		}
		i++;
	}
	if (buf[i] == '\n' && i != size - 1)
		next_buf = ft_substr(buf, i + 1, ft_strlen(buf) - (i + 1));
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buf, i + 2);
	free(buf);
	if (!line)
	{
		free(next_buf);
		next_buf = NULL;
		return (NULL);
	}
	return (line);
}
