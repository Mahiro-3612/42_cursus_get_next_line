/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 09:00:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	t_list		*list;
	char		*buf;
	char		*line;
	ssize_t		bytes_read;

	list = NULL;
	if (next_buf)
	{
		ft_lstadd_back(&list, &next_buf);
		ft_clear(NULL, &next_buf);
	}
	bytes_read = 1;
	while (!has_newline(list, bytes_read) && bytes_read > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_clear(&list, &next_buf);
			ft_clear(NULL, &buf);
			return(NULL) ;
		}
		if (bytes_read > 0)
			ft_lstadd_back(&list, &buf);
		ft_clear(NULL, &buf);
	}
	line = get_until_newline(&list, &next_buf);
	return (line);
}
