#include "cub3d.h"

int	find_player_minimap(t_cub3d *cub)
{
	int x = 0;
	int	y = 0;
	while (y < cub->map_info.height)
	{
		x = 0;
		while (x < cub->map_info.width)
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'W' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E')
			{
				cub->player.x = x + 0.5;
				cub->player.y = y + 0.5;
				if (cub->map[y][x] == 'N')
				{
					cub->player.dir_x = 0;
					cub->player.dir_y = -1;
				}
				else if (cub->map[y][x] == 'W')
				{
					cub->player.dir_x = -1;
					cub->player.dir_y = 0;
				}
				else if (cub->map[y][x] == 'S')
				{
					cub->player.dir_x = 0;
					cub->player.dir_y = -1;
				}
				else
				{
					cub->player.dir_x = 1;
					cub->player.dir_y = 0;
				}
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_player(t_cub3d *cub)
{
	int player_x = cub->player.x * cub->tile_size;
	int player_y = cub->player.y * cub->tile_size;
	
	for (int y = -2; y <= 2; y++)
	{
		for (int x = -2; x <= 2; x++)
		{
			int draw_x = player_x + x;
			int draw_y = player_y + y;
			if (draw_x >= 0 && draw_x < cub->game.win_width && 
				draw_y >= 0 && draw_y < cub->game.win_height)
				my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0x00FF0000);
		}
	}
	return (0);
}

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
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	init_side_dist(ray);
}

int	dda(t_cub3d *cub)
{
	t_ray	*ray;

	ray = cub->ray;
	init_ray(cub);
	while (cub->map[ray->map_y][ray->map_x] != '1')
	{
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
	
int draw_ray(t_cub3d *cub)
{
	float	ray_x;
	float	ray_y;
	float	step;
	int		map_x;
	int		map_y;

	ray_x = cub->player.x;
	ray_y = cub->player.y;
	step = 0.01;
	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (cub->map[map_y][map_x] == '1')
			break;
		my_mlx_pixel_put(&cub->img, ray_x * cub->tile_size, ray_y * cub->tile_size, 0x0000FF00);
		ray_x += cub->player.dir_x * step;
		ray_y += cub->player.dir_y * step;
	}
	return (0);
}