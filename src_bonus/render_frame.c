#include "cub3d_bonus.h"

void	draw_floor_ceiling(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->game.win_height / 2)
	{
		x = 0;
		while (x < cub->game.win_width)
		{
			my_mlx_pixel_put(&cub->img, x, y, cub->texture.ceiling_color);
			x++;
		}
		y++;
	}
	while (y < cub->game.win_height)
	{
		x = 0;
		while (x < cub->game.win_width)
		{
			my_mlx_pixel_put(&cub->img, x, y, cub->texture.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_textured_line(t_cub3d *cub, t_ray *ray, t_img *img, int col)
{
	int	y;
	int	tex_y;
	int	start;
	int	end;

	if (col < 0 || col >= cub->game.win_width)
		return ;
	clamp_values(&ray->tex_x, cub->tex_door.width);
	start = (int)ray->draw_start;
	end = (int)ray->draw_end;
	if (start < 0)
		start = 0;
	if (end > cub->game.win_height)
		end = cub->game.win_height;
	y = start;
	while (y < end)
	{
		tex_y = (y - ray->draw_start) * img->height / ray->line_height;
		clamp_values(&tex_y, img->height);
		my_mlx_pixel_put(&cub->img, col, y,
			img->texture_table[tex_y][ray->tex_x]);
		y++;
	}
}


void	draw_one_wall(t_cub3d *cub, t_ray *ray, int col, int flag)
{
	if (flag == 2) // DOOR
		draw_door(cub, ray, col);
	else if (ray->hit_side == 0 && ray->dir_x > 0) // EAST
	{
		ray->tex_x = cub->tex_e.width - (int)(ray->wallX
				* (double)(cub->tex_e.width)) - 1;
		draw_textured_line(cub, ray, &cub->tex_e, col);
	}
	else if (ray->hit_side == 0 && ray->dir_x < 0) // WEST
	{
		ray->tex_x = (int)(ray->wallX * (double)(cub->tex_w.width));
		draw_textured_line(cub, ray, &cub->tex_w, col);
	}
	else if (ray->hit_side == 1 && ray->dir_y < 0) // NORTH
	{
		ray->tex_x = cub->tex_n.width - (int)(ray->wallX
				* (double)(cub->tex_n.width)) - 1;
		draw_textured_line(cub, ray, &cub->tex_n, col);
	}
	else // SOUTH
	{
		ray->tex_x = (int)(ray->wallX * (double)(cub->tex_s.width));
		draw_textured_line(cub, ray, &cub->tex_s, col);
	}
}

int	draw_all_walls(t_cub3d *cub)
{
	t_ray	ray;
	int		i;
	int		flag;

	i = 0;
	while (i < cub->game.win_width)
	{
		ray.cameraX = 2 * i / (double)(cub->game.win_width - 1) - 1;
		init_ray(cub, &ray);
		flag = dda_loop(cub, &ray);
		calc_draw_values(cub, &ray);
		draw_one_wall(cub, &ray, i, flag);
		i++;
	}
	return (0);
}

int	render_frame(void *param)
{
	t_cub3d	*cub;
	int		total_pixels;
	double	delta_time;

	cub = (t_cub3d *)param;
	if (!cub->img.addr)
		return (0);
	total_pixels = cub->game.win_width * cub->game.win_height
		* (cub->img.bits_per_pixel / 8);
	delta_time = (get_current_time() - cub->game.last_frame_time) / 1000.0;
	ft_memset(cub->img.addr, 0, total_pixels);
	door_update(cub, delta_time);
	handle_inputs(cub, delta_time);
	draw_floor_ceiling(cub);
	draw_all_walls(cub);
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}
