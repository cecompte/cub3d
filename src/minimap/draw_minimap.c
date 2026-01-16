#include "cub3d.h"

int	print_tile(t_cub3d *cub, int width, int height, int color)
{
	int border_color = 0x00404040;
	
	for (int y = 0; y < cub->minimap.tile_size; y++)
	{
		for (int x = 0; x < cub->minimap.tile_size; x++)
		{
			int draw_x = cub->minimap.offset_x + width + x;
			int draw_y = cub->minimap.offset_y + height + y;
			int pixel_color = color;
			if (x == 0 || y == 0 || x == cub->minimap.tile_size - 1 || y == cub->minimap.tile_size - 1)
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
				print_tile(cub, width * cub->minimap.tile_size, height * cub->minimap.tile_size, 0x00808080);
			else
				print_tile(cub, width * cub->minimap.tile_size, height * cub->minimap.tile_size, 0x00FFFFFF);
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
	