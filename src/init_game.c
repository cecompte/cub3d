#include "cub3d.h"

void	init_game(t_cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height, "Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height);
	cub->img.img = mlx_new_image(cub->mlx_ptr, cub->game.win_width, cub->game.win_height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length,
								&cub->img.endian);
}
