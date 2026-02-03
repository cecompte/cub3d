/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/03 15:26:36 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	print_tile(t_cub3d *cub, int width, int height, int color)
{
	int	x;
	int	y;
	int	draw_x;
	int	draw_y;

	y = 0;
	while (y < cub->minimap.tile_size)
	{
		x = 0;
		while (x < cub->minimap.tile_size)
		{
			draw_x = cub->minimap.offset_x + width + x;
			draw_y = cub->minimap.offset_y + height + y;
			if (draw_x >= 0 && draw_x < cub->game.win_width
				&& draw_y >= 0 && draw_y < cub->game.win_height)
				my_mlx_pixel_put(&cub->img, draw_x, draw_y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_grid(t_cub3d *cub)
{
	int	width;
	int	height;

	height = 0;
	while (height < cub->map_info.height)
	{
		width = 0;
		while (width < cub->map_info.width)
		{
			if (cub->map_grid[height][width] == '1')
				print_tile(cub, width * cub->minimap.tile_size,
					height * cub->minimap.tile_size, 0x00008880);
			else if (cub->map_grid[height][width] == 'D')
				print_tile(cub, width * cub->minimap.tile_size,
					height * cub->minimap.tile_size, 0x00FFC0CB);
			else
				print_tile(cub, width * cub->minimap.tile_size,
					height * cub->minimap.tile_size, cub->texture.floor_color);
			width++;
		}
		height++;
	}
	return (0);
}

void	init_minimap(t_cub3d *cub)
{
	cub->minimap.offset_x = 10;
	cub->minimap.offset_y = 10;
	cub->minimap.tile_size = 10;
	cub->minimap.width = cub->minimap.tile_size * cub->map_info.width;
	cub->minimap.height = cub->minimap.tile_size * cub->map_info.height;
}

int	render_minimap(t_cub3d *cub)
{
	draw_grid(cub);
	draw_player_minimap(cub);
	return (0);
}
