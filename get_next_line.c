/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:07:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/05/21 20:50:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_get_line(char *buf, unsigned int max_len,
					int *nl_found, char **line);

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	offset;
	char		*str;
	int			nl_found;

	if (!offset)
	{
		buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		ft_memset(buf, '\0', BUFFER_SIZE + 1);
		if (read(fd, buf, BUFFER_SIZE) <= 0)
		{
			free(buf);
			return (NULL);
		}
	}
	nl_found = 0;
	offset = (offset + ft_get_line(buf + offset,
				BUFFER_SIZE - offset, &nl_found, &str)) % BUFFER_SIZE;
	if (!offset || (offset && buf[offset] == '\0'))
	{
		free(buf);
		if (!offset && !nl_found)
			return (ft_strjoin(str, get_next_line(fd)));
		offset = 0;
	}
	return (str);
}

unsigned int	ft_get_line(char *buf, unsigned int max_len,
					int *nl_found, char **line)
{
	unsigned long long	i;

	i = 0;
	while (i < max_len && buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (i < max_len && buf[i] != '\0')
	{
		*nl_found = 1;
		i++;
	}
	// *line = (char *) malloc((i + 1) * sizeof(char));
	ft_strlcpy(line, buf, i);
	return (i);
}

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
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("found line: %s\n", line);
			sleep(1);
			i++;	
		}
	}
	return (0);
}