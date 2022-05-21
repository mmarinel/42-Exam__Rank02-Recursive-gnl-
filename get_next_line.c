/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:07:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/05/21 23:39:04 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_get_line(char *buf, unsigned int max_len,
					int *nl_found, char **line);

static t_bool	gnl_buffer_read_from_file(char **buf, int fd, int buffer_size);
static t_bool	gnl_get_line_from_buffer(char **buf, int *offset, char **str, int buffer_size);

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	offset;
	char		*str;
	t_bool		nl_found;

	// printf("\nNEW BEGINNING\n");
	// fflush(stdout);
	if (!offset)
	{
		if (e_false == gnl_buffer_read_from_file(&buf, fd, 0))
			return (NULL);
		// printf("\nOFFSET IS 0\n");
	}
	nl_found = gnl_get_line_from_buffer(&buf, &offset, &str, 0);
	// printf("str: %s\nnl_found: %d\n", str, nl_found);
	// exit(0);
	// offset = (offset + ft_get_line(buf + offset,
	// 			BUFFER_SIZE - offset, &nl_found, &str)) % BUFFER_SIZE;
	if (!offset || (offset && buf[offset] == '\0'))
	{
		free(buf);
		if (!offset && !nl_found)
		{
			// printf("HEREHERE\n");
			// fflush(stdout);
			return (ft_strjoin(str, get_next_line(fd), e_true, e_true));
		}
		offset = 0;
	}
	// printf("***str: %s\noffset: %d*****\n", str, offset);
	return (str);
}

static t_bool	gnl_buffer_read_from_file(char **buf, int fd, int buffer_size)
{
	if (buffer_size)
		;
	*buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	ft_memset(*buf, '\0', BUFFER_SIZE + 1);
	if (read(fd, *buf, BUFFER_SIZE) <= 0)
	{
		free(*buf);
		return (e_false);
	}
	return (e_true);
}

static t_bool	gnl_get_line_from_buffer(char **buf, int *offset, char **str, int buffer_size)
{
	t_bool	nl_found;
	int		line_len;
	int		buffer_start;
	int		i;

	if (buffer_size)
		;
	nl_found = e_false;
	i = *offset;
	buffer_start = *offset;
	while (i < BUFFER_SIZE)
	{
		if ((*buf)[i] == '\n'
			|| (*buf)[i] == '\0')
		{
			if ((*buf)[i] == '\n')
				nl_found = e_true;
			break ;
		}
		i++;
	}
	// printf("BOOOOOOOOO\n");
	// fflush(stdout);
	if ((*buf)[i] == '\0')
	{
		line_len = i - *offset;
		// *offset = i + 1;
	}
	else
	{
		line_len = i - *offset + 1;
		// *offset = (i + 1);
	}
	if (i == BUFFER_SIZE
		|| i == BUFFER_SIZE - 1
		|| (*buf)[i] == '\0')
	{
		// printf("MAOMETTO ER KETCHUP ?\n");
		*offset = 0;
	}
	else
		*offset = (i + 1) % BUFFER_SIZE;
	// printf("i: %d\nline_len: %d\noffset: %d\nnl_found: %d\n", i, line_len, *offset, nl_found);
	// fflush(stdout);
	ft_strlcpy(str, *buf + buffer_start, line_len);
	return (nl_found);
}

// unsigned int	ft_get_line(char *buf, unsigned int max_len,
// 					int *nl_found, char **line)
// {
// 	unsigned long long	i;

// 	i = 0;
// 	while (i < max_len && buf[i] != '\0' && buf[i] != '\n')
// 		i++;
// 	if (i < max_len && buf[i] != '\0')
// 	{
// 		*nl_found = 1;
// 		i++;
// 	}
// 	// *line = (char *) malloc((i + 1) * sizeof(char));
// 	ft_strlcpy(line, buf, i);
// 	return (i);
// }

int	main(int argc, char const *argv[])
{
	const char	*file_path;
	char		*line;
	int			fd;
	int			i = 0;

	if (argc == 2)
	{
		file_path = *(argv + 1);
		fd = open(file_path, O_RDONLY | O_CREAT);
		if (fd < 0)
			return (0);
		do
		{
			line = get_next_line(fd);
			printf("found line: %s\n", line);
			sleep(1);
			i++;
		} while (line);
	}
	return (0);
}