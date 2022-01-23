/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:14:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/01/23 15:54:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_get_line(char **str, int fd);
unsigned int	ft_get_line_rec(char **s1, char **s2, char **res,
					int fd, t_fd_buffer *fd_buf);
unsigned int	ft_line_len(char *line, unsigned int max_len, int *nl_found);

char	*get_next_line(int fd)
{
	char				*str;
	static t_fd_buffer	*fd_buf;

	if (!ft_get_line(&str, fd))
		str = NULL;
	if (fd_buf && !(fd_buf->buf))
	{
		free(fd_buf);
		fd_buf = NULL;
	}
	return (str);
}

unsigned int	ft_get_line(char **str, int fd)
{
	static t_fd_buffer	*fd_buf;
	unsigned int		str_len;
	char				*str_rest;
	char				*res;
	int					nl_found;

	if (!fd_buf)
	{
		fd_buf = (t_fd_buffer *) malloc(sizeof(t_fd_buffer));
		fd_buf->offset = 0;
	}
	if (!fd_buf->offset)
	{
		fd_buf->buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		ft_memset(fd_buf->buf, '\0', BUFFER_SIZE + 1);
		fd_buf->bytes_read = read(fd, fd_buf->buf, BUFFER_SIZE);
		if (fd_buf->bytes_read <= 0)
		{
			free(fd_buf->buf);
			fd_buf->buf = NULL;
			if (fd_buf->bytes_read < 0)
				return (0);
			*str = NULL;
			return (1);
		}
	}
	nl_found = 0;
	str_len = ft_line_len(fd_buf->buf + fd_buf->offset,
			BUFFER_SIZE - fd_buf->offset, &nl_found);
	*str = (char *) malloc((str_len + 1) * sizeof(char));
	ft_strlcpy(str, fd_buf->buf + fd_buf->offset, str_len);
	fd_buf->offset = (fd_buf->offset + str_len) % BUFFER_SIZE;
	if (!(fd_buf->offset) || (nl_found && fd_buf->buf[fd_buf->offset] == '\0'))
	{
		// printf("BUFFER: %s, ultima pos: %c\n", fd_buf->buf, fd_buf->buf[fd_buf->offset]);
		free(fd_buf->buf);
		fd_buf->buf = NULL;
		if (!(fd_buf->offset) && !nl_found)
		{
			if (!ft_get_line_rec(str, &str_rest, &res, fd, fd_buf))
				return (0);
		}
	}
	return (1);
}

unsigned int	ft_get_line_rec(char **s1, char **s2, char **res, int fd, t_fd_buffer *fd_buf)
{
	fd_buf->offset = 0;
	if (!ft_get_line(s2, fd))
		return (0);
	*res = ft_strjoin(*s1, *s2);
	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	*s1 = *res;
	return (1);
}

unsigned int	ft_line_len(char *line, unsigned int max_len, int *nl_found)
{
	unsigned long long	i;

	i = 0;
	while (i < max_len && line[i] != '\n')
		i++;
	if (i < max_len)
	{
		*nl_found = 1;
		return (i + 1);
	}
	return (i);
}

// int	main(int argc, char const *argv[])
// {
// 	const char	*file_path;
// 	char		*line;
// 	int			fd;
// 	int			i = 0;

// 	if (argc == 2)
// 	{
// 		file_path = *(argv + 1);
// 		fd = open(file_path, O_RDONLY | O_CREAT);
// 		if (fd < 0)
// 			return (0);
// 		while ((line = get_next_line(fd)) != NULL)
// 		{
// 			printf("found line: %s\n", line);
// 			i++;	
// 		}
// 	}
// 	return (0);
// }
