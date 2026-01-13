#include "cub3d.h"

void	init_game(t_cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height, "Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height);
	mlx_loop(cub->mlx_ptr);
}
