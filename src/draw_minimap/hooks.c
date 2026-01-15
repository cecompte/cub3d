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
void	rotate(t_cub3d *cub, double angle)
{
	double	new_dir_y;
	double	new_dir_x;
	double	new_plane_y;
	double	new_plane_x;

	new_dir_x = cub->player.dir_x * cos(angle) - cub->player.dir_y * sin(angle);
	new_dir_y = cub->player.dir_x * sin(angle) + cub->player.dir_y * cos(angle);
	new_plane_x = cub->player.plane_x * cos(angle) - cub->player.plane_y * sin(angle);
	new_plane_y = cub->player.plane_x * sin(angle) + cub->player.plane_y * cos(angle);
	cub->player.dir_x = new_dir_x;
	cub->player.dir_y = new_dir_y;
	cub->player.plane_x = new_plane_x;
	cub->player.plane_y = new_plane_y;
}

void	update_position(t_cub3d *cub, int move_x, int move_y)
{
	double	try_y;
	double	try_x;

	try_x = cub->player.x + move_x * 0.005;
	if (cub->map[(int)cub->player.y][(int)try_x] != '1')
    	cub->player.x = try_x;
	
	try_y = cub->player.y + move_y * 0.005;
	if (cub->map[(int)try_y][(int)cub->player.x] != '1')
    	cub->player.y = try_y;
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
		update_position(cub, 0, 1);
	if (cub->input.up == 1)
		update_position(cub, 0, -1);
	if (cub->input.left == 1)
		update_position(cub, -1, 0);
	if (cub->input.right == 1)
		update_position(cub, 1, 0);
	if (cub->input.rotate_left == 1)
		rotate(cub, -0.005);
	if (cub->input.rotate_right == 1)
		rotate(cub, 0.005);
	render_minimap(cub);
	return (0);
}
