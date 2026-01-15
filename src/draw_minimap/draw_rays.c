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

void	init_ray(t_cub3d *cub)
{
	t_ray	*ray;

	ray = cub->ray;
	ray->pos_x = cub->player.x;
	ray->pos_y = cub->player.y;
	ray->dir_x = cub->player.dir_x;
	ray->dir_y = cub->player.dir_y;
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

void	dda_step(t_ray *ray, double *curr_x, double *curr_y)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		*curr_x = ray->map_x + (ray->step_x < 0 ? 1 : 0);
		*curr_y = ray->pos_y + (*curr_x - ray->pos_x) * ray->dir_y / ray->dir_x;
		ray->hit_side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		*curr_y = ray->map_y + (ray->step_y < 0 ? 1 : 0);
		*curr_x = ray->pos_x + (*curr_y - ray->pos_y) * ray->dir_x / ray->dir_y;
		ray->hit_side = 1;
	}
}

int	draw_ray_dda(t_cub3d *cub)
{
	t_ray	*ray;
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;

	ray = cub->ray;
	init_ray(cub);
	start_x = ray->pos_x;
	start_y = ray->pos_y;
	end_x = start_x;
	end_y = start_y;
	while (1)
	{
		if (ray->map_x < 0 || ray->map_x >= cub->map_info.width || 
			ray->map_y < 0 || ray->map_y >= cub->map_info.height)
			break;
		if (cub->map[ray->map_y][ray->map_x] == '1')
			break;
		dda_step(ray, &end_x, &end_y);
	}
	draw_segment(cub, start_x, start_y, end_x, end_y, 0x00FF0000);
	return (0);
}