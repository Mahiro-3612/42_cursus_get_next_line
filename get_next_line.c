/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/22 10:07:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	char		*buf;
	char		*tmp;
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
	// bufありnext_buf=NULL
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
			tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			if (!tmp)
			{
				free(buf);
				return (NULL);
			}
			bytes_read = read(fd, tmp, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				free(buf);
				free(tmp);
				return (NULL);
			}
			else if (bytes_read == 0)
			{
				free(tmp);
				break ;
			}
			buf = ft_strjoin_and_free(buf, &tmp);
			if (!buf)
				return (NULL);
			size += bytes_read;
			free(tmp);
		}
		i++;
	}
	// bufありnext_buf=NULL
	if (buf[i] == '\n' && i != size - 1)
	{
		next_buf = ft_substr_with_free(buf, i + 1, ft_strlen(buf) - (i + 1));
		if (!next_buf)
			return (NULL);
	}
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
	{
		free(buf);
		if (next_buf)
			free(next_buf);
		next_buf = NULL;
		return (NULL);
	}
	ft_strlcpy(line, buf, i + 2);
	free(buf);
	return (line);
}
