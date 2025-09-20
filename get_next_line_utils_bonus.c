/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:44 by codespace         #+#    #+#             */
/*   Updated: 2025/09/20 05:29:21 by codespace        ###   ########.fr       */
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
	return (ft_strlcpy(dest, s + start, len + 1), dest);
}

void	ft_clear(t_list **list, char **content)
{
	t_list	*current;
	t_list	*next_node;

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