/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:44 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 05:54:25 by codespace        ###   ########.fr       */
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

ssize_t	ft_lstadd_back(int fd, t_list **list, char **content)
{
	t_list	*new;
	t_list	*last;
	ssize_t	bytes_read;

	if (!*content)
	{
		*content = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!*content)
		{
			ft_clear(list, content);
			return (-1);
		}
		bytes_read = read(fd, *content, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			ft_clear(list, content);
			return (bytes_read);
		}
	}
	else
		bytes_read = 1;
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
	{
		ft_clear(list, content);
		return (-1);
	}
	ft_strlcpy(new->content, *content, ft_strlen(*content) + 1);
	free(*content);
	*content = NULL;
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
	return (bytes_read);
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

char	*get_until_newline(t_list *list, char **next_buf)
{
	char	*buf;
	t_list	*current;
	char	*line;
	size_t	i;

	buf = NULL;
	line = NULL;
	current = list;
	while (current != NULL)
	{
		buf = ft_strjoin_and_free(&buf, current->content);
		current = current->next;
	}
	ft_clear(&list, next_buf);
	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	line = ft_substr(buf, 0, i + 1);
	if (buf[i])
		*next_buf = ft_substr(buf, i + 1, ft_strlen(buf) - (i + 1));
	else
		*next_buf = NULL;
	free(buf);
	return (line);
}

size_t	has_newline(t_list *list)
{
	t_list	*current;
	size_t	i;

	current = list;
	while (current != NULL)
	{
		i = 0;
		while ((current->content)[i] && (current->content)[i] != '\n')
			i++;
		if ((current->content)[i] == '\n')
			return (1);
		current = current->next;
	}
	return (0);
}