/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:14:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/01/21 20:03:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_get_line(char **str, int fd);
unsigned int	ft_get_line_rec(char **s1, char **s2, char **res, int fd);
unsigned int	ft_line_len(char *line, unsigned int max_len);

char	*get_next_line(int fd)
{
	char	*str;

	if (!ft_get_line(&str, fd))
		return (NULL);
	return (str);
}

unsigned int	ft_get_line(char **str, int fd)
{
	static char			*buf;
	static unsigned int	offset;
	unsigned int		str_len;
	char				*str_rest;
	char				*res;

	if (!offset)
	{
		buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (read(fd, buf, BUFFER_SIZE) <= 0)
			return (0);
	}
	str_len = ft_line_len(buf + offset, BUFFER_SIZE - offset);
	*str = (char *) malloc((str_len + 1) * sizeof(char));
	ft_strlcpy(str, buf + offset, str_len);
	offset = (offset + str_len) % BUFFER_SIZE;
	if (!offset || offset == BUFFER_SIZE - 1)
	{
		free(buf);
		if (!offset
			&& !ft_get_line_rec(str, &str_rest, &res, fd))
			return (0);
	}
	return (1);
}

unsigned int	ft_get_line_rec(char **s1, char **s2, char **res, int fd)
{
	if (!ft_get_line(s2, fd))
		return (0);
	*res = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	*s1 = *res;
	return (1);
}

unsigned int	ft_line_len(char *line, unsigned int max_len)
{
	unsigned long long	i;

	i = 0;
	while (i < max_len && line[i] != '\n')
		i++;
	return (i);
}

int	main(int argc, char const *argv[])
{
	const char	*file_path;
	char		*line;
	int			fd;

	if (argc == 2)
	{
		file_path = *(argv + 1);
		fd = open(file_path, O_RDONLY | O_CREAT);
		if (fd < 0)
			return (0);
		while ((line = get_next_line(fd)) != NULL)
			printf("found line: %s\n", line);
	}
	return (0);
}
