/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakurai <msakurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/09/25 19:54:19 by msakurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

static void	ft_lstadd_back_and_free(t_list **list, char **content)
{
	t_list	*new;
	t_list	*last;

	if (!content || !*content)
		return ;
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (ft_clear(list, content));
	ft_strlcpy(new->content, *content, BUFFER_SIZE + 1);
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	ft_clear(NULL, content);
}

static size_t	has_newline(t_list *list, ssize_t bytes_read)
{
	t_list	*current;
	ssize_t	i;
	char	c;

	current = list;
	while (current != NULL)
	{
		i = 0;
		while (i < bytes_read)
		{
			c = (current->content)[i];
			if (c && c != '\n')
				i++;
			else
				break ;
		}
		if (i < bytes_read && (current->content)[i] == '\n')
			return (1);
		current = current->next;
	}
	return (0);
}

static char	*get_buf(t_list **list)
{
	char	*buf;
	t_list	*current;
	size_t	len;
	size_t	offset;

	current = *list;
	len = 0;
	while (current)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	buf = ft_calloc(len + 1, sizeof(char));
	if (!buf)
		return (NULL);
	current = *list;
	offset = 0;
	while (current)
	{
		len = ft_strlen(current->content);
		ft_strlcpy(buf + offset, current->content, len + 1);
		offset += len;
		current = current->next;
	}
	return (buf);
}

static char	*get_until_newline(t_list **list, char **next_buf)
{
	char	*buf;
	char	*line;
	size_t	i;

	if (!list || !*list)
		return (ft_clear(list, next_buf), NULL);
	buf = get_buf(list);
	if (!buf)
		return (ft_clear(list, next_buf), NULL);
	ft_clear(list, next_buf);
	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	line = NULL;
	if (i != 0 || buf[0] != '\0')
		line = ft_substr(buf, 0, i + 1);
	if (i + 1 < ft_strlen(buf))
	{
		*next_buf = ft_substr(buf, i + 1, ft_strlen(buf) - (i + 1));
		if (!*next_buf)
			ft_clear(NULL, &line);
	}
	if (!line)
		ft_clear(list, next_buf);
	return (free(buf), line);
}

char	*get_next_line(int fd)
{
	static char	*next_buf[FOPEN_MAX];
	t_list		*list;
	char		*buf;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	list = NULL;
		if (fd >= 0 && fd < FOPEN_MAX && next_buf[fd])
		ft_lstadd_back_and_free(&list, &next_buf[fd]);
	if (fd < 0 || fd >= FOPEN_MAX || (next_buf[fd] && !list))
		return (NULL);
	bytes_read = 1;
	while (!has_newline(list, bytes_read) && bytes_read > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (ft_clear(&list, &next_buf[fd]), NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_clear(&list, &next_buf[fd]), ft_clear(NULL, &buf), NULL);
		if (bytes_read > 0)
			ft_lstadd_back_and_free(&list, &buf);
		ft_clear(NULL, &buf);
	}
	return (get_until_newline(&list, &next_buf[fd]));
}
