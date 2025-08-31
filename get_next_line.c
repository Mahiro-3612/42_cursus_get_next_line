/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:42 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 12:32:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_lstadd_back(t_list **list, char **content)
{
	t_list	*new;
	t_list	*last;

	if (!content || !*content)
		return ;
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
	{
		ft_clear(list, content);
		return ;
	}
	ft_strlcpy(new->content, *content, ft_strlen(*content) + 1);
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
}

static size_t	has_newline(t_list *list, ssize_t bytes_read)
{
	t_list	*current;
	ssize_t	i;
	char	str;

	current = list;
	while (current != NULL)
	{
		i = 0;
		str = (current->content)[i];
		while (str && str != '\n' && i < bytes_read)
			i++;
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

	buf = NULL;
	if (!list || !*list)
		return (NULL);
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

char	*get_until_newline(t_list **list, char **next_buf)
{
	char	*buf;
	char	*line;
	size_t	i;
	size_t	len;

	buf = NULL;
	line = NULL;
	if (!list || !*list)
		return (NULL);
	buf = get_buf(list);
	if (!buf)
	{
		ft_clear(list, next_buf);
		return (NULL);
	}
	ft_clear(list, next_buf);
	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (i == 0 && buf[0] == '\0')
		line = NULL;
	else
		line = ft_substr(buf, 0, i + 1);
	len = ft_strlen(buf);
	if (i + 1 < len)
	{
		*next_buf = ft_substr(buf, i + 1, len - (i + 1));
		if (!*next_buf)
		{
			free(line);
			line = NULL;
		}
	}
	else
		*next_buf = NULL;
	free(buf);
	return (line);
}

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
		if (!list)
			return (NULL);
	}
	bytes_read = 1;
	while (!has_newline(list, bytes_read) && bytes_read > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
		{
			ft_clear(&list, &next_buf);
			return (NULL);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_clear(&list, &next_buf);
			ft_clear(NULL, &buf);
			return (NULL);
		}
		if (bytes_read > 0)
		{
			ft_lstadd_back(&list, &buf);
			if (!list)
			{
				ft_clear(NULL, &buf);
				return (NULL);
			}
		}
		ft_clear(NULL, &buf);
	}
	line = get_until_newline(&list, &next_buf);
	if (!line)
		ft_clear(&list, &next_buf);
	return (line);
}
