/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 04:45:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_buf = NULL;
	t_list		*list;
	char		*line;

	list = NULL;
	ft_lstadd_back(fd, &list, &next_buf);
	if (!list)
		return (NULL);
	while (!has_newline(list))
	{
		ft_lstadd_back(fd, &list, NULL);
		if (!list)
			return (NULL);
	}
	line = get_until_newline(list, &next_buf);
	return (line);
}
