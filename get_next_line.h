/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:14:58 by mmarinel          #+#    #+#             */
/*   Updated: 2022/05/22 10:58:05 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> // DA TOGLIERE
# include <stdio.h> // DA TOGLIERE

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
// # define BUFFER_SIZE 42
# define READ_ERROR -1

typedef struct s_fd_buffer {
	char			*buf;
	int				buffer_size;
	unsigned int	offset;
}	t_fd_buffer;

typedef enum e_bool
{
	e_true = 1,
	e_false = 0
}	t_bool;

char	*get_next_line(int fd);
void	ft_strcpy(char *dst, char *src);
void	ft_strlcpy(char **dst, char *src, int dst_len);
// size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *pre, char const *post, t_bool free_pre, t_bool free_post);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

#endif