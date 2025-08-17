/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/17 09:09:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buf;
	static char	*next_buf = NULL;
	char	*line;

	if (!next_buf)
	{
		buf = read_until_n(fd, BUFFER_SIZE);
		printf("buf is %s\n", buf);
		if (!buf)
			return (NULL);
	}
	else
	{
		buf = ft_calloc(BUFFER_SIZE + 2, sizeof(char));
		ft_strlcpy(buf, next_buf, BUFFER_SIZE + 2);
		free(next_buf);
		printf("buf is %s\n", buf);
	}
	next_buf = read_until_n(fd, BUFFER_SIZE + 1);
	printf("next_buf is %s\n", next_buf);
	if (!next_buf)
	{
		free(buf);
		return (NULL);
	}
	line = ft_strdup(buf);
	free(buf);
	return (line);
}
