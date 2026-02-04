/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <esergeev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:30 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:01:18 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	save_player(t_player *player, int i, int j, char dir)
{
	player->x = j + 0.5;
	player->y = i + 0.5;
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	player->plane_x = -0.66 * player->dir_y;
	player->plane_y = 0.66 * player->dir_x;
}

int	find_player(char **map, t_player *player)
{
	int		i;
	int		j;
	int		player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				save_player(player, i, j, map[i][j]);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count < 1)
		return (ft_putstr_fd("Error\nNo player found\n", 2), 1);
	if (player_count > 1)
		return (ft_putstr_fd("Error\nMultiple players found\n", 2), 1);
	return (0);
}

static char	**make_rect_map(char **map, int height, int width)
{
	int		i;
	int		j;
	char	**rect_map;

	i = 0;
	rect_map = malloc(sizeof(char *) * (height + 1));
	if (!rect_map)
		return (NULL);
	while (i < height)
	{
		rect_map[i] = malloc(sizeof(char) * (width + 1));
		if (!rect_map[i])
			return (free_tabc(rect_map), NULL);
		j = 0;
		while (map[i][j])
		{
			rect_map[i][j] = map[i][j];
			j++;
		}
		while (j < width)
			rect_map[i][j++] = ' ';
		rect_map[i][j] = '\0';
		i++;
	}
	return (rect_map[i] = NULL, rect_map);
}

static void	restore_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	parce_map_grid(char **map, t_cub3d *cub)
{
	char	**rect_map;

	cub->map_info.height = get_map_height(map);
	cub->map_info.width = get_max_width(map, cub->map_info.height);
	if (check_empty_line(map))
		return (ft_putstr_fd("Error\nEmpty line in map\n", 2), 1);
	if (find_player(map, &cub->player) != 0)
		return (1);
	if (check_chars(map) != 0)
		return (ft_putstr_fd("Error\nInvalid character in map\n", 2), 1);
	rect_map = make_rect_map(map, cub->map_info.height, cub->map_info.width);
	if (!rect_map)
		return (ft_putstr_fd("Error\nWall is not closed\n", 2), 1);
	if (check_islands(rect_map, cub->map_info))
		return (free_tabc(rect_map), ft_putstr_fd("Error\nMap has open zero(s)\n",
				2), 1);
	if (flood_fill(rect_map, &cub->map_info, (int)cub->player.y,
			(int)cub->player.x) != 0)
	{
		free_tabc(rect_map);
		return (ft_putstr_fd("Error\nWall is not closed\n", 2), 1);
	}
	restore_map(rect_map);
	cub->map_grid = rect_map;
	return (0);
}
