/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:32:16 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 04:32:50 by codespace        ###   ########.fr       */
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
char	*ft_strjoin_and_free(char **s1, char *s2);
void	ft_lstadd_back(int fd, t_list **list, char **content);
size_t	ft_strlen(char *s);
char	*get_until_newline(t_list *list, char **next_buf);
size_t	has_newline(t_list *list);
void	ft_clear(t_list **list, char **content);