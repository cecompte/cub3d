#include "cub3d.h"

#include "cub3d.h"

void	draw_floor_ceiling(t_cub3d *cub)
{
	int x;
	int	y;

	y = 0;
	cub->texture.floor_color = 0x7a7a7a; // to remove (test only)
	cub->texture.ceiling_color = 0x4b0082; // to remove (test only)
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

int	draw_vertical_line(t_cub3d *cub, int col, double draw_start, double draw_end, int wall_color)
{
	int	y;
	int	start;
	int	end;

	if (col < 0 || col >= cub->game.win_width)
		return (0);
	start = (int)draw_start;
	end = (int)draw_end;
	if (start < 0)
		start = 0;
	if (end > cub->game.win_height)
		end = cub->game.win_height;
	y = start;
	while (y < end)
	{
		my_mlx_pixel_put(&cub->img, col, y, wall_color);
		y++;
	}
	return (0);
}
void	draw_textured(t_cub3d *cub, t_ray *ray, t_img *img, int col)
{
	int y;
	int relative_y;
	int tex_y;
	int	start;
	int	end;

	if (col < 0 || col >= cub->game.win_width)
		return;
	start = (int)ray->draw_start;
	end = (int)ray->draw_end;
	if (start < 0)
		start = 0;
	if (end > cub->game.win_height)
		end = cub->game.win_height;
	y = start;
	while (y < end)
	{
		relative_y = y - ray->draw_start;
		tex_y = relative_y * img->height / ray->line_height;
		my_mlx_pixel_put(&cub->img, col, y, img->texture_table[tex_y][ray->tex_x]);
		y++;
	}
}

int	draw_walls(t_cub3d *cub)
{
	t_ray	ray;
	int 	i;

	// if (!cub->map || cub->map_info.width == 0 || cub->map_info.height == 0)
	// 	return (0);
	i = 0;
	while (i < cub->game.win_width)
	{
		ray.cameraX = 2 * i / (double)(cub->game.win_width - 1) - 1;
		init_ray(cub, &ray);
		dda_loop(cub, &ray);
		draw_rays_utils(cub, &ray);
		if (ray.hit_side == 0 && ray.dir_x > 0) // EAST
		{
			ray.tex_x = (int)(ray.wallX * (double)(cub->tex_e.width));
			ray.tex_x = cub->tex_e.width - ray.tex_x - 1;
			draw_textured(cub, &ray, &cub->tex_e, i);
		}
		else if (ray.hit_side == 0 && ray.dir_x < 0) // WEST
			draw_vertical_line(cub, i, ray.draw_start, ray.draw_end, 0x00FF0000);
		else if (ray.hit_side == 1 && ray.dir_y < 0) // NORTH
			draw_vertical_line(cub, i, ray.draw_start, ray.draw_end, 0x000000FF);
		else // SOUTH (dir_y > 0) or any unmatched case
			draw_vertical_line(cub, i, ray.draw_start, ray.draw_end, 0x00C0CBFF);
		i++;
	}
	return (0);
}

void	handle_inputs(t_cub3d *cub)
{
	if (cub->input.down == 1)
		update_position(cub, -1, 0, cub->game.speed);
	if (cub->input.up == 1)
		update_position(cub, 1, 0, cub->game.speed);
	if (cub->input.left == 1)
		update_position(cub, 0, -1, cub->game.speed);
	if (cub->input.right == 1)
		update_position(cub, 0, 1, cub->game.speed);
	if (cub->input.rotate_left == 1)
		rotate(cub, -cub->game.speed);
	if (cub->input.rotate_right == 1)
		rotate(cub, cub->game.speed);
}

int	render_frame(void *param)
{
	t_cub3d	*cub;
	int	total_pixels;

	cub = (t_cub3d *)param;
	if (!cub->img.addr)
		return (0);
	total_pixels = cub->game.win_width * cub->game.win_height * (cub->img.bits_per_pixel / 8);
	ft_memset(cub->img.addr, 0, total_pixels);
	handle_inputs(cub);
	draw_floor_ceiling(cub);
	draw_walls(cub);
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}
