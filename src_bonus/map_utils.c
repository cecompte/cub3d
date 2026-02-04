/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <esergeev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 18:40:05 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n' || map[i][0] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	get_max_width(char **map, int height)
{
	int	max;
	int	len;
	int	i;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = (int)ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	check_empty_line(char **map)
{
	int	i;
	int	j;
	int	on_map;

	i = -1;
	on_map = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
			j++;
		if (map[i][j] == '\0')
		{
			if (on_map == 2)
				return (1);
			on_map = 1;
		}
		else if (on_map == 1)
			on_map = 2;
	}
	return (0);
}

int	flood_fill(char **map, t_map_info *info, int y, int x)
{
	if (y < 0 || y >= info->height || x < 0 || x >= info->width)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'D')
		return (0);
	map[y][x] = 'V';
	if (flood_fill(map, info, y + 1, x) || flood_fill(map, info, y - 1, x)
		|| flood_fill(map, info, y, x + 1) || flood_fill(map, info, y, x - 1))
		return (1);
	return (0);
}

int	check_chars(char **map)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W' || map[i][j] == '1' || map[i][j] == '0'
				|| map[i][j] == ' ' || map[i][j] == '\n' || map[i][j] == 'D' )
				j++;
			else
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}
