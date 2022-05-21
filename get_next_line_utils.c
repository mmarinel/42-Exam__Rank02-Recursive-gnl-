/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/05/21 22:47:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize)
{
	unsigned long	i;

	i = 0;
	if (dstsize)
	{
		// printf("dstsize: %zu\n", dstsize);
		// fflush(stdout);
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

char	*ft_strjoin(char const *pre, char const *post, t_bool free_pre, t_bool free_post)
{
	size_t	pre_len;
	size_t	post_len;
	char	*s_join;

	if (!pre)
		return (ft_strjoin(post, "", free_post, e_false));
	if (!post)
		return (ft_strjoin(pre, "", free_pre, e_false));
	pre_len = ft_strlen(pre);
	post_len = ft_strlen(post);
	s_join = (char *) malloc((pre_len + post_len + 1) * sizeof(char));
	if (s_join == NULL)
		return (NULL);
	ft_strcpy((char *) s_join, (char *) pre);
	ft_strcpy((char *) s_join + pre_len, (char *) post);
	if (free_pre && pre)
		free((char *) pre);
	if (free_post && post)
		free((char *) post);
	return (s_join);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
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
