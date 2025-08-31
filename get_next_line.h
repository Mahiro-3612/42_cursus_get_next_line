/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:32:16 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 12:30:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

typedef struct s_list
{
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *s);
void	ft_clear(t_list **list, char **content);
