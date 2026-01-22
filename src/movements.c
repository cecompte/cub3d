#include "cub3d.h"

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

void	update_position(t_cub3d *cub, int forward, int strafe, double speed)
{
	double	try_y;
	double	try_x;

	try_x = cub->player.x + (forward * cub->player.dir_x + strafe * cub->player.plane_x) * speed;
	if (cub->map_grid[(int)cub->player.y][(int)try_x] != '1')
		cub->player.x = try_x;
	
	try_y = cub->player.y + (forward * cub->player.dir_y + strafe * cub->player.plane_y) * speed;
	if (cub->map_grid[(int)try_y][(int)cub->player.x] != '1')
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

void	handle_inputs(t_cub3d *cub)
{
	size_t	current_time;
	double	delta_time;

	current_time = get_current_time();
	delta_time = (current_time - cub->game.last_frame_time) / 1000.0;
	cub->game.last_frame_time = current_time;
	if (cub->input.down == 1)
		update_position(cub, -1, 0, cub->game.move_speed * delta_time);
	if (cub->input.up == 1)
		update_position(cub, 1, 0, cub->game.move_speed * delta_time);
	if (cub->input.left == 1)
		update_position(cub, 0, -1, cub->game.move_speed * delta_time);
	if (cub->input.right == 1)
		update_position(cub, 0, 1, cub->game.move_speed * delta_time);
	if (cub->input.rotate_left == 1)
		rotate(cub, -cub->game.rotation_speed * delta_time);
	if (cub->input.rotate_right == 1)
		rotate(cub, cub->game.rotation_speed * delta_time);
}