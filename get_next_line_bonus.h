/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakurai <msakurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:32:16 by codespace         #+#    #+#             */
/*   Updated: 2025/09/25 22:27:04 by msakurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>

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

#endif
