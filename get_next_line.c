/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 05:53:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	t_list		*list;
	char		*line;
	ssize_t		bytes_read;

	list = NULL;
	bytes_read = ft_lstadd_back(fd, &list, &next_buf);
	if (!list)
	{
		if (next_buf)
			ft_clear(&list, &next_buf);
		return (NULL);
	}
	while (!has_newline(list) && bytes_read > 0)
	{
		bytes_read = ft_lstadd_back(fd, &list, &next_buf);
		if (!list)
		{
			if (next_buf)
				ft_clear(&list, &next_buf);
			return (NULL);
		}
	}
	line = get_until_newline(list, &next_buf);
	return (line);
}
