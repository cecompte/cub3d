/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <esergeev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:12:00 by esergeev          #+#    #+#             */
/*   Updated: 2026/01/19 18:33:46 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const	*s2)
{
	char		*res;
	char		*start;
	const char	*p1;
	const char	*p2;

	p1 = s1;
	p2 = s2;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	start = res;
	while (*p1)
		*res++ = *p1++;
	while (*p2)
		*res++ = *p2++;
	*res = '\0';
	return (start);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned const char	*buf;
	unsigned char		*res;

	if (n == 0 || dest == src)
		return (dest);
	buf = (unsigned const char *)src;
	res = (unsigned char *)dest;
	while (n--)
	{
		*res = *buf;
		res++;
		buf++;
	}
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
