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
				cub->pos.x = x;
				cub->pos.y = y;
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

int	draw_minimap(t_cub3d *cub)
{
	int x = 0;
	int	y = 0;
	cub->img.img = mlx_new_image(cub->mlx_ptr, cub->game.win_width, cub->game.win_height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length,
									&cub->img.endian);
	// Clear entire image to black first
	while (y < cub->game.win_height)
	{
		x = 0;
		while (x < cub->game.win_width)
		{
			my_mlx_pixel_put(&cub->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	find_player_minimap(cub);
	// Draw player as a small circle (5x5 pixels) - scale up the position for visibility
	int player_x = cub->pos.x * 10;  // Scale up for visibility on minimap
	int player_y = cub->pos.y * 10;
	
	for (y = -2; y <= 2; y++)
	{
		for (x = -2; x <= 2; x++)
		{
			int draw_x = player_x + x;
			int draw_y = player_y + y;
			if (draw_x >= 0 && draw_x < cub->game.win_width && 
				draw_y >= 0 && draw_y < cub->game.win_height)
				my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0x0000FF00); // Green
		}
	}
	
	return (0);
}