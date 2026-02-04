/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:42:30 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate(t_cub3d *cub, double angle)
{
	double	new_dir_y;
	double	new_dir_x;
	double	new_plane_y;
	double	new_plane_x;

	new_dir_x = cub->player.dir_x * cos(angle) - cub->player.dir_y * sin(angle);
	new_dir_y = cub->player.dir_x * sin(angle) + cub->player.dir_y * cos(angle);
	new_plane_x = cub->player.plane_x * cos(angle) - cub->player.plane_y
		* sin(angle);
	new_plane_y = cub->player.plane_x * sin(angle) + cub->player.plane_y
		* cos(angle);
	cub->player.dir_x = new_dir_x;
	cub->player.dir_y = new_dir_y;
	cub->player.plane_x = new_plane_x;
	cub->player.plane_y = new_plane_y;
}

void	update_position(t_cub3d *cub, int forward, int strafe, double speed)
{
	double	try_y;
	double	try_x;

	try_x = cub->player.x + (forward * cub->player.dir_x + strafe
			* cub->player.plane_x) * speed;
	if (cub->map_grid[(int)cub->player.y][(int)try_x] != '1'
		&& can_pass_door(cub, (int)try_x, (int)cub->player.y))
		cub->player.x = try_x;
	try_y = cub->player.y + (forward * cub->player.dir_y + strafe
			* cub->player.plane_y) * speed;
	if (cub->map_grid[(int)try_y][(int)cub->player.x] != '1'
		&& can_pass_door(cub, (int)cub->player.x, (int)try_y))
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
	else if (keycode == SPACE_KEY)
		toggle_door(cub);
	else if (keycode == M_KEY)
	{
		cub->game.mouse_enabled = !cub->game.mouse_enabled;
		if (cub->game.mouse_enabled)
			mlx_mouse_hide(cub->mlx_ptr, cub->win_ptr);
		else
			mlx_mouse_show(cub->mlx_ptr, cub->win_ptr);
	}
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

void	handle_inputs(t_cub3d *cub, double delta_time)
{
	cub->game.last_frame_time = get_current_time();
	if (cub->input.down == 1)
		update_position(cub, -1, 0, cub->game.move_speed * delta_time);
	if (cub->input.up == 1)
		update_position(cub, 1, 0, cub->game.move_speed * delta_time);
	if (cub->input.left == 1)
		update_position(cub, 0, -1, cub->game.move_speed * delta_time);
	if (cub->input.right == 1)
		update_position(cub, 0, 1, cub->game.move_speed * delta_time);
	if (cub->input.rotate_left == 1)
		rotate(cub, -cub->game.rotation_angle * delta_time);
	if (cub->input.rotate_right == 1)
		rotate(cub, cub->game.rotation_angle * delta_time);
}
