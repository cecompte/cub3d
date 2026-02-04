/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:36:55 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_mouse(int x, int y, t_cub3d *cub)
{
	int		centre_x;
	int		centre_y;
	int		delta;
	double	mouse_sensitivity;

	if (!cub->game.mouse_enabled)
		return (0);
	(void)y;
	centre_x = cub->game.win_width / 2;
	centre_y = cub->game.win_height / 2;
	delta = x - centre_x;
	if (delta == 0)
		return (0);
	mouse_sensitivity = cub->game.rotation_angle * 0.003;
	rotate(cub, delta * mouse_sensitivity);
	mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, centre_x, centre_y);
	return (0);
}
