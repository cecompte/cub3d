#include "cub3d_bonus.h"

void	door_update(t_cub3d *cub, double delta_time)
{
	int	i;
	i = 0;
	while (i < cub->door_count)
	{
		if (cub->doors[i].state == OPENING)
		{
			cub->doors[i].openness += cub->doors[i].opening_speed * delta_time;
			if (cub->doors[i].openness >= 1.0)
			{
				cub->doors[i].openness = 1.0;
				cub->doors[i].state = OPEN;
			}
		}
		if (cub->doors[i].state == CLOSING)
		{
			cub->doors[i].openness -= cub->doors[i].opening_speed * delta_time;
			if (cub->doors[i].openness <= 0.0)
			{
				cub->doors[i].openness = 0.0;
				cub->doors[i].state = CLOSED;
			}
		}
		i++;
	}
}

void	draw_door(t_cub3d *cub, t_ray *ray, int col)
{
	int		index;
	double	shifted_texture_x;

	index = cub->door_index[ray->map_y][ray->map_x];
	shifted_texture_x = ray->wallX - cub->doors[index].openness;
	ray->tex_x = (int)(shifted_texture_x * (double)(cub->tex_door.width));
    draw_textured_line(cub, ray, &cub->tex_door, col);
}
