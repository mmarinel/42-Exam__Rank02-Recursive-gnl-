/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/01/22 22:35:50 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize)
{
	unsigned long	i;

	i = 0;
	if (dstsize)
	{
		*dst = (char *) malloc((dstsize + 1) * sizeof(char));
		while (src[i] != '\0' && i < dstsize)
		{
			*(*dst + i) = src[i];
			i++;
		}
		*(*dst + i) = '\0';
	}
	while (src[i] != '\0')
		i++;
	return ((size_t) i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s_join;

	if (!s1)
		return (ft_strjoin(s2, ""));
	if (!s2)
		return (ft_strjoin(s1, ""));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s_join = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (s_join == NULL)
		return (NULL);
	return ((char *) ft_memcpy(
			ft_memcpy(s_join, s1, s1_len) + s1_len,
			s2,
			s2_len + 1) - s1_len);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;
	size_t		i;

	ptr_dest = dst;
	ptr_src = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = b;
	while (i < len)
		s[i++] = c;
	return (b);
}
