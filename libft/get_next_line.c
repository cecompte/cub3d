/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:55:41 by esergeev          #+#    #+#             */
/*   Updated: 2025/05/27 15:03:04 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_remain(char *save)
{
	char	*newline;
	char	*remain;

	newline = ft_strchr(save, '\n');
	if (!newline)
	{
		free(save);
		return (NULL);
	}
	remain = ft_strdup(newline + 1);
	return (free(save), remain);
}

static char	*get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save || !*save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, save, i);
	line[i] = '\0';
	return (line);
}

static char	*read_until_newline(int fd, char *save)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_r;
	char	*tmp;

	bytes_r = 1;
	while (!ft_strchr(save, '\n') && bytes_r != 0)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (bytes_r < 0)
		{
			free(save);
			return (NULL);
		}
		buffer[bytes_r] = '\0';
		tmp = ft_strjoin(save, buffer);
		free(save);
		save = tmp;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_until_newline(fd, save);
	if (!save || !*save)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = get_line(save);
	tmp = get_remain(save);
	save = tmp;
	return (line);
}
