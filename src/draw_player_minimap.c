#include "cub3d.h"

void	draw_segment(t_cub3d *cub, double x0, double y0, double x1, double y1, int color)
{
	int draw_x;
	int	draw_y;
	double	steps;
	double	x;
	double	y;
	int		i;

	steps = fmax(fabs(x1 - x0), fabs(y1 - y0)) * cub->minimap.tile_size;
	if (steps == 0)
		steps = 1;
	x = x0;
	y = y0;
	i = 0;
	while (i <= (int)steps && i < 10000)
	{
		draw_x = cub->minimap.offset_x + (int)(x * cub->minimap.tile_size);
		draw_y = cub->minimap.offset_y + (int)(y * cub->minimap.tile_size);
		if (draw_x >= 0 && draw_x < cub->game.win_width &&
			draw_y >= 0 && draw_y < cub->game.win_height)
			my_mlx_pixel_put(&cub->img, draw_x, draw_y, color);
		x += (x1 - x0) / steps;
		y += (y1 - y0) / steps;
		i++;
	}
}

int	draw_direction(t_cub3d *cub)
{
	double	start_x = cub->player.x;
	double	start_y = cub->player.y;
	double	end_x = cub->player.x + cub->player.dir_x;
	double	end_y = cub->player.y + cub->player.dir_y;
	draw_segment(cub, start_x, start_y, end_x, end_y, 0x00FF0000);
	return (0);
}

int	draw_plane(t_cub3d *cub)
{
	double	start_x = cub->player.x - cub->player.plane_x;
	double	start_y = cub->player.y - cub->player.plane_y;
	double	end_x = cub->player.x + cub->player.plane_x;
	double	end_y = cub->player.y + cub->player.plane_y;
	draw_segment(cub, start_x, start_y, end_x, end_y, 0x000000FF);
	return(0);
}

int	draw_player_minimap(t_cub3d *cub)
{
	int player_x = cub->minimap.offset_x + cub->player.x * cub->minimap.tile_size;
	int player_y = cub->minimap.offset_y + cub->player.y * cub->minimap.tile_size;

	for (int y = -2; y <= 2; y++)
	{
		for (int x = -2; x <= 2; x++)
		{
			int draw_x = player_x + x;
			int draw_y = player_y + y;
			if (draw_x >= 0 && draw_x < cub->game.win_width &&
				draw_y >= 0 && draw_y < cub->game.win_height)
				my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0x00FF0000);
		}
	}
	draw_direction(cub);
	draw_plane(cub);
	return (0);
}
