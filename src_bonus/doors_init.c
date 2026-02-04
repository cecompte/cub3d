/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:37 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 15:56:14 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_doors(char **map)
{
	int		i;
	int		j;
	int		door_count;

	door_count = 0;
	j = 0;
	i = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				door_count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (door_count);
}

void	init_door(t_door *door)
{
	door->map_x = 0;
	door->map_y = 0;
	door->state = CLOSED;
	door->openness = 0;
	door->opening_speed = 0.8;
}

int	init_door_index(t_cub3d *cub)
{
	int	y;
	int	x;
	int	door_idx;

	if (!cub->door_count)
		return (cub->door_index = NULL, 0);
	cub->door_index = malloc(cub->map_info.height * sizeof(int *));
	if (!cub->door_index)
		return (1);
	y = -1;
	door_idx = 0;
	while (++y < cub->map_info.height)
	{
		cub->door_index[y] = malloc(cub->map_info.width * sizeof(int));
		if (!cub->door_index[y])
			return (free_array(cub->door_index, y), cub->door_index = NULL, 1);
		ft_memset(cub->door_index[y], -1, cub->map_info.width * sizeof(int));
		x = -1;
		while (++x < cub->map_info.width)
			if (cub->map_grid[y][x] == 'D')
				cub->door_index[y][x] = door_idx++;
	}
	return (0);
}

int	set_slide_direction(t_cub3d *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->map_info.height)
	{
		x = -1;
		while (++x < cub->map_info.width)
		{
			if (cub->map_grid[y][x] == 'D')
			{
				cub->doors[cub->door_index[y][x]].map_x = x;
				cub->doors[cub->door_index[y][x]].map_y = y;
				if (cub->map_grid[y][x - 1] == '1'
					&& cub->map_grid[y][x + 1] == '1')
					cub->doors[cub->door_index[y][x]].direction = VERTICAL;
				else if (cub->map_grid[y - 1][x] == '1'
					&& cub->map_grid[y + 1][x] == '1')
					cub->doors[cub->door_index[y][x]].direction = HORIZONTAL;
				else
					return (1);
			}
		}
	}
	return (0);
}

int	init_all_doors(t_cub3d *cub)
{
	int		i;

	cub->door_count = count_doors(cub->map_grid);
	if (init_door_index(cub))
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
	if (!cub->door_count)
		return (cub->doors = NULL, 0);
	cub->doors = malloc(cub->door_count * sizeof(t_door));
	if (!cub->doors)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
	i = 0;
	while (i < cub->door_count)
	{
		init_door(&cub->doors[i]);
		i++;
	}
	if (set_slide_direction(cub))
		return (ft_putstr_fd("Error\nDoor invalid\n", 2), 1);
	return (0);
}
