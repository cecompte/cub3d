#include "cub3d.h"

int	find_player_minimap(t_cub3d *cub)
{
	int x = 0;
	int	y = 0;
	while (y < cub->map_info.height)
	{
		x = 0;
		while (x < cub->map_info.width)
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'W' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E')
			{
				cub->pos.x = x + 0.5;
				cub->pos.y = y + 0.5;
				if (cub->map[y][x] == 'N')
				{
					cub->pos.dir_x = 0;
					cub->pos.dir_y = -1;
				}
				else if (cub->map[y][x] == 'W')
				{
					cub->pos.dir_x = -1;
					cub->pos.dir_y = 0;
				}
				else if (cub->map[y][x] == 'S')
				{
					cub->pos.dir_x = 0;
					cub->pos.dir_y = -1;
				}
				else
				{
					cub->pos.dir_x = 1;
					cub->pos.dir_y = 0;
				}
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_player(t_cub3d *cub)
{
	int player_x = cub->pos.x * cub->tile_size;
	int player_y = cub->pos.y * cub->tile_size;
	
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
	return (0);
}

int	draw_direction(t_cub3d *cub)
{
	int length = 20;
	int start_x = cub->pos.x * cub->tile_size;
	int start_y = cub->pos.y * cub->tile_size;
	int x = 0;
	int y = 0;;

	while (y <= length && x <= length)
	{
		my_mlx_pixel_put(&cub->img, start_x + cub->pos.dir_x * x, start_y + cub->pos.dir_y * y, 0x00FF0000);
		y++;
		x++;
	}
	return (0);
}

