#include "cub3d.h"

int	find_player(t_cub3d *cub)
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
	// // Clear entire image to black first
	// while (y < cub->game.win_height)
	// {
	// 	x = 0;
	// 	while (x < cub->game.win_width)
	// 	{
	// 		my_mlx_pixel_put(&cub->img, x, y, 0x00000000);
	// 		x++;
	// 	}
	// 	y++;
	// }
	// Draw player as a small circle (5x5 pixels)
	if (!find_player(cub))
		return (printf("no player\n"));
	for (y = -2; y <= 2; y++)
		for (x = -2; x <= 2; x++)
			my_mlx_pixel_put(&cub->img, cub->pos.x + x, cub->pos.y + y, 0x0000FF00); // Green
	
	return (0);
}