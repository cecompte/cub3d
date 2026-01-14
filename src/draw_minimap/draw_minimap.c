#include "cub3d.h"

int	print_tile(t_cub3d *cub, int width, int height, int color)
{
	int border_color = 0x00404040;
	
	for (int y = 0; y < cub->tile_size; y++)
	{
		for (int x = 0; x < cub->tile_size; x++)
		{
			int draw_x = width + x;
			int draw_y = height + y;
			int pixel_color = color;
			if (x == 0 || y == 0 || x == cub->tile_size - 1 || y == cub->tile_size - 1)
				pixel_color = border_color;
			
			if (draw_x >= 0 && draw_x < cub->game.win_width && 
				draw_y >= 0 && draw_y < cub->game.win_height)
				my_mlx_pixel_put(&cub->img, draw_x, draw_y, pixel_color);
		}
	}
	return (0);
}
int	draw_grid(t_cub3d *cub)
{
	int	width;
	int	height = 0;
	while (height < cub->map_info.height)
	{
		width = 0;
		while (width < cub->map_info.width)
		{
			if (cub->map[height][width] == '1')
				print_tile(cub, width * cub->tile_size, height * cub->tile_size, 0x00808080);
			else
				print_tile(cub, width * cub->tile_size, height * cub->tile_size, 0x00FFFFFF);
			width++;
		}
		height++;
	}
	return (0);
}

int	init_minimap(t_cub3d *cub)
{
	int	win_height = cub->map_info.height * cub->tile_size;
	int	win_width = cub->map_info.width * cub->tile_size;

	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, win_width, win_height, "cub3d");
	cub->img.img = mlx_new_image(cub->mlx_ptr, win_width, win_height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length,
								&cub->img.endian);
	find_player_minimap(cub);
	draw_grid(cub);
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}

int	render_minimap(t_cub3d *cub)
{
	draw_grid(cub);
	draw_player(cub);
	draw_ray(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}
	