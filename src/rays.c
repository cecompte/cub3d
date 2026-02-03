/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:30 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/03 20:39:13 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_side_dist(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	init_ray(t_cub3d *cub, t_ray *ray)
{
	ray->pos_x = cub->player.x;
	ray->pos_y = cub->player.y;
	ray->dir_x = cub->player.dir_x + cub->player.plane_x * ray->camera_x;
	ray->dir_y = cub->player.dir_y + cub->player.plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	init_side_dist(ray);
}

int	dda_loop(t_cub3d *cub, t_ray *ray)
{
	int	max_steps;

	max_steps = 0;
	while (max_steps++ < 1000)
	{
		if (cub->map_grid[ray->map_y][ray->map_x] == '1')
			break ;
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->hit_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->hit_side = 1;
		}
	}
	return (0);
}

void	calc_draw_values(t_cub3d *cub, t_ray *ray)
{
	if (ray->hit_side == 0)
		ray->perp_wall_dist = (ray->map_x - cub->player.x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - cub->player.y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_height = cub->game.win_height / ray->perp_wall_dist;
	ray->draw_start = cub->game.win_height / 2 - ray->line_height / 2;
	ray->draw_end = cub->game.win_height / 2 + ray->line_height / 2;
	if (ray->hit_side == 0)
		ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor((ray->wall_x));
}
