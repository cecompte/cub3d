/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:30:18 by cecompte          #+#    #+#             */
/*   Updated: 2026/01/13 14:51:02 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_calloc(size_t nmemb, size_t size)
{
	char	*tmp;
	size_t	i;

	if (nmemb > 0)
	{
		if ((size_t)-1 / nmemb < size)
			return (NULL);
	}
	tmp = malloc(nmemb * size);
	if (tmp == NULL)
		return (0);
	i = 0;
	while (i < size * nmemb)
		tmp[i++] = 0;
	return (tmp);
}

char	*join_free(char *buf1, char *buf2)
{
	char	*tmp;

	if (!buf1)
		buf1 = gnl_calloc(1, 1);
	if (!buf1 || !buf2)
		return (NULL);
	tmp = ft_strjoin(buf1, buf2);
	free(buf1);
	return (tmp);
}

size_t	index_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	return (i);
}

char	*read_file(int fd, char *stash)
{
	char	*buff;
	ssize_t	bytes_read;

	buff = gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buff[bytes_read] = 0;
		stash = join_free(stash, buff);
	}
	return (free(buff), stash);
}

char	*next_stash(char *stash, char *line)
{
	char	*tmp;
	size_t	i;
	size_t	len_stash;
	size_t	len_line;

	if (!stash || !line)
		return (NULL);
	i = index_nl(stash);
	len_stash = ft_strlen(stash);
	len_line = ft_strlen(line);
	if (len_stash > len_line)
		tmp = ft_strndup(stash + i + 1, len_stash - i + 1);
	else
		tmp = NULL;
	free(stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_strndup(stash, index_nl(stash) + 1);
	if (!line)
		return (free (stash), NULL);
	stash = next_stash(stash, line);
	return (line);
}
