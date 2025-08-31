/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:44 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 10:57:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

void	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	max_len;

	if (ft_strlen(s) <= start)
	{
		dest = ft_calloc(1, sizeof(char));
		if (!dest)
			return (NULL);
		return (dest);
	}
	max_len = ft_strlen(s) - start;
	if (max_len < len)
		len = max_len;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}

char	*ft_strjoin_and_free(char **s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;

	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	dest = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!dest)
	{
		ft_clear(NULL, s1);
		return (NULL);
	}
	ft_strlcpy(dest, *s1, s1_len + 1);
	ft_strlcpy(dest + s1_len, s2, s2_len + 1);
	ft_clear(NULL, s1);
	return (dest);
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

void	ft_lstadd_back(t_list **list, char **content)
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

void	ft_clear(t_list **list, char **content)
{
    t_list  *current;
    t_list  *next_node;

	if (content)
	{
		free(*content);
		*content = NULL;
	}
    if (!list || !*list)
        return ;
    current = *list;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *list = NULL;
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

size_t	has_newline(t_list *list, ssize_t bytes_read)
{
	t_list	*current;
	ssize_t	i;

	current = list;
	while (current != NULL)
	{
		i = 0;
		while ((current->content)[i] && (current->content)[i] != '\n' && i < bytes_read)
			i++;
		if (i < bytes_read && (current->content)[i] == '\n')
			return (1);
		current = current->next;
	}
	return (0);
}
