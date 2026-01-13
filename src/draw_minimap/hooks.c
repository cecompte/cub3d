#include "cub3d.h"

int	close_game(t_cub3d *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img.img);
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	// free all structures
	free(cub->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_cub3d *cub)
{
	if (keycode == ESC)
		close_game(cub);
	if (keycode == UP)
		cub->input.up = 1;
	else if (keycode == DOWN)
		cub->input.down = 1;
	else if (keycode == LEFT)
		cub->input.left = 1;
	else if (keycode == RIGHT)
		cub->input.right = 1;
	else if (keycode == LEFT_ARROW)
		cub->input.rotate_left = 1;
	else if (keycode == RIGHT_ARROW)
		cub->input.rotate_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub3d *cub)
{
	if (keycode == UP)
		cub->input.up = 0;
	if (keycode == DOWN)
		cub->input.down = 0;
	if (keycode == LEFT)
		cub->input.left = 0;
	if (keycode == RIGHT)
		cub->input.right = 0;
	if (keycode == LEFT_ARROW)
		cub->input.rotate_left = 0;
	if (keycode == RIGHT_ARROW)
		cub->input.rotate_right = 0;
	return (0);
}

int	render_frame(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (cub->input.down == 1)
		cub->pos.y += 0.005;
	if (cub->input.up == 1)
		cub->pos.y -= 0.005;
	if (cub->input.left == 1)
		cub->pos.x -= 0.005;
	if (cub->input.right == 1)
		cub->pos.x += 0.005;
	render_minimap(cub);
	return (0);
}
