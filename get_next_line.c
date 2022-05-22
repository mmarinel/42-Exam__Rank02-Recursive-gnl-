/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:07:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/05/22 11:55:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_next_line_rec(int fd, t_fd_buffer *buf_handle);


static t_bool	gnl_buffer_read_from_file(t_fd_buffer *buf_handle, int fd);
static t_bool	gnl_get_line_from_buffer(t_fd_buffer *buf_handle, char **str);

char	*get_next_line(int fd)
{
	static t_fd_buffer	buf_handle = (t_fd_buffer){NULL, BUFFER_SIZE, 0};

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf_handle.offset == 0)
		buf_handle.buffer_size = BUFFER_SIZE;
	return (get_next_line_rec(fd, &buf_handle));
}

static char	*get_next_line_rec(int fd, t_fd_buffer *buf_handle)
{
	char		*str;
	t_bool		nl_found;

	if (buf_handle->offset == 0)
	{
		if (e_false == gnl_buffer_read_from_file(buf_handle, fd))
			return (NULL);
	}
	nl_found = gnl_get_line_from_buffer(buf_handle, &str);
	if (buf_handle->offset == 0 || buf_handle->buf[buf_handle->offset] == '\0')
	{
		free(buf_handle->buf);
		if (buf_handle->offset == 0 && !nl_found)
		{
			buf_handle->buffer_size = buf_handle->buffer_size + 5;
			return (ft_strjoin(str, get_next_line_rec(fd, buf_handle),
						e_true, e_true));
		}
		buf_handle->offset = 0;
	}
	return (str);
}

static t_bool	gnl_buffer_read_from_file(t_fd_buffer *buf_handle, int fd)
{
	buf_handle->buf = (char *) malloc((buf_handle->buffer_size + 1) * sizeof(char));
	ft_memset(buf_handle->buf, '\0', buf_handle->buffer_size + 1);
	if (read(fd, buf_handle->buf, buf_handle->buffer_size) <= 0)
	{
		free(buf_handle->buf);
		return (e_false);
	}
	return (e_true);
}

static t_bool	gnl_get_line_from_buffer(t_fd_buffer *buf_handle, char **str)
{
	t_bool	nl_found;
	int		line_len;
	int		buffer_start;
	int		i;

	nl_found = e_false;
	i = buf_handle->offset;
	buffer_start = buf_handle->offset;
	while (i < buf_handle->buffer_size)
	{
		if (buf_handle->buf[i] == '\n'
			|| buf_handle->buf[i] == '\0')
		{
			if (buf_handle->buf[i] == '\n')
				nl_found = e_true;
			break ;
		}
		i++;
	}
	if (buf_handle->buf[i] == '\0')
		line_len = i - buf_handle->offset;
	else
		line_len = i - buf_handle->offset + 1;
	if (i == buf_handle->buffer_size - 1
		|| buf_handle->buf[i] == '\0')
		buf_handle->offset = 0;
	else
		buf_handle->offset = i + 1;
	ft_strlcpy(str, buf_handle->buf + buffer_start, line_len);
	return (nl_found);
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
// 		do
// 		{
// 			line = get_next_line(fd);
// 			printf("found line: %s\n", line);
// 			sleep(1);
// 			i++;
// 		} while (line);
// 	}
// 	return (0);
// }
