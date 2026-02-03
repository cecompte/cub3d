/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/03 15:22:44 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	door_update(t_cub3d *cub, double delta_time)
{
	int	i;

	i = 0;
	while (i < cub->door_count)
	{
		if (cub->doors[i].state == OPENING)
		{
			cub->doors[i].openness += cub->doors[i].opening_speed * delta_time;
			if (cub->doors[i].openness >= 1.0)
			{
				cub->doors[i].openness = 1.0;
				cub->doors[i].state = OPEN;
			}
		}
		if (cub->doors[i].state == CLOSING)
		{
			cub->doors[i].openness -= cub->doors[i].opening_speed * delta_time;
			if (cub->doors[i].openness <= 0.0)
			{
				cub->doors[i].openness = 0.0;
				cub->doors[i].state = CLOSED;
			}
		}
		i++;
	}
}

void	draw_door(t_cub3d *cub, t_ray *ray, int col)
{
	int		index;
	double	shifted_texture_x;

	index = cub->door_index[ray->map_y][ray->map_x];
	shifted_texture_x = ray->wallX - cub->doors[index].openness;
	ray->tex_x = (int)(shifted_texture_x * (double)(cub->tex_door.width));
	draw_textured_line(cub, ray, &cub->tex_door, col);
}

void	toggle_door(t_cub3d *cub)
{
	int		check_x;
	int		check_y;
	int		index;
	double	max_dist;

	max_dist = 2.0;
	check_x = (int)(cub->player.x + cub->player.dir_x * max_dist);
	check_y = (int)(cub->player.y + cub->player.dir_y * max_dist);
	if (check_x < 0 || check_x >= cub->map_info.width
		|| check_y < 0 || check_y >= cub->map_info.height)
		return ;
	if (cub->map_grid[check_y][check_x] != 'D')
		return ;
	index = cub->door_index[check_y][check_x];
	if (cub->doors[index].state == CLOSED)
		cub->doors[index].state = OPENING;
	else if (cub->doors[index].state == OPEN)
		cub->doors[index].state = CLOSING;
}
