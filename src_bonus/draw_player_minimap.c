/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_minimap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/05 12:07:49 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_segment(t_cub3d *cub, double start[], double end[], int color)
{
	int		draw_x;
	int		draw_y;
	double	steps;
	double	dx;
	double	dy;

	steps = fmax(fabs(end[0] - start[0]), fabs(end[1] - start[1]))
		* cub->minimap.tile_size;
	if (steps == 0)
		steps = 1;
	dx = (end[0] - start[0]) / steps;
	dy = (end[1] - start[1]) / steps;
	while (steps-- > 0)
	{
		draw_x = cub->minimap.offset_x
			+ (int)(start[0] * cub->minimap.tile_size);
		draw_y = cub->minimap.offset_y
			+ (int)(start[1] * cub->minimap.tile_size);
		if (draw_x >= 0 && draw_x < cub->game.win_width && draw_y >= 0
			&& draw_y < cub->game.win_height)
			my_mlx_pixel_put(&cub->img, draw_x, draw_y, color);
		start[0] += dx;
		start[1] += dy;
	}
}

int	draw_direction(t_cub3d *cub)
{
	double	start[2];
	double	end[2];

	start[0] = cub->player.x;
	start[1] = cub->player.y;
	end[0] = cub->player.x + cub->player.dir_x;
	end[1] = cub->player.y + cub->player.dir_y;
	draw_segment(cub, start, end, 0x00FF0000);
	return (0);
}

int	draw_plane(t_cub3d *cub)
{
	double	start[2];
	double	end[2];

	start[0] = cub->player.x - cub->player.plane_x;
	start[1] = cub->player.y - cub->player.plane_y;
	end[0] = cub->player.x + cub->player.plane_x;
	end[1] = cub->player.y + cub->player.plane_y;
	draw_segment(cub, start, end, 0x000000FF);
	return (0);
}

int	draw_player_minimap(t_cub3d *cub)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			draw_x = cub->minimap.offset_x
				+ (int)(cub->player.x * cub->minimap.tile_size) + x;
			draw_y = cub->minimap.offset_y
				+ (int)(cub->player.y * cub->minimap.tile_size) + y;
			my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0x00FF0000);
			x++;
		}
		y++;
	}
	draw_direction(cub);
	draw_plane(cub);
	return (0);
}
