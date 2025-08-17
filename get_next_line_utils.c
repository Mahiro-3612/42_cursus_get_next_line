/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:31:44 by codespace         #+#    #+#             */
/*   Updated: 2025/08/17 09:08:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	copy = ft_calloc(len + 1, sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}

char	*read_until_n(int fd, size_t size)
{
	ssize_t	read_bytes;
	ssize_t	i;
	size_t	is_valid;
	char	*tmp;
	char	*buf;

	tmp = ft_calloc(size, sizeof(char));
	if (!tmp)
		return (NULL);
	read_bytes = read(fd, tmp, size);
	if (read_bytes <= 0)
	{
		free(tmp);
		return (NULL);
	}
	i = 0;
	while (i < read_bytes && tmp[i] != '\n')
		i++;
	is_valid = !(i == read_bytes);
	if (is_valid)
	{
		buf = ft_calloc(i + 1, sizeof(char));
		if (!buf)
		{
			free(tmp);
			return (NULL);
		}
		ft_strlcpy(buf, tmp, i + 1);
	}
	else
	{
		buf = ft_calloc(i + 2, sizeof(char));
		if (!buf)
		{
			free(tmp);
			return (NULL);
		}
		ft_strlcpy(buf, tmp, i + 1);
		buf[i] = '\n';
		buf[i + 1] = '\0';
	}
	return (buf);
}
