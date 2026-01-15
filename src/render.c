#include "cub3d.h"

int	draw_vertical_line(t_cub3d *cub, int col, double draw_start, double draw_end, int wall_color)
{
	int	y;
	int	start;
	int	end;

	if (col < 0 || col >= WIDTH)
		return (0);
	start = (int)draw_start;
	end = (int)draw_end;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	y = start;
	while (y < end)
	{
		my_mlx_pixel_put(&cub->img, col, y, wall_color);
		y++;
	}
	return (0);
}

int	render_fullmap(t_cub3d *cub)
{
	t_ray	ray;
	int 	i;
	double	line_height;
	double	perp_wall_dist;
	double	draw_start;
	double	draw_end;

	if (!cub->map || cub->map_info.width == 0 || cub->map_info.height == 0)
		return (0);
	i = 0;
	while (i < WIDTH)
	{
		ray.cameraX = 2 * i / (double)(WIDTH - 1) - 1;
		init_ray(cub, &ray);
		dda_loop(cub, &ray);
		if (ray.hit_side == 0)
			perp_wall_dist = (ray.map_x - cub->player.x + (1 - ray.step_x) /2) / ray.dir_x;
		else
			perp_wall_dist = (ray.map_y - cub->player.y + (1 - ray.step_y) /2) / ray.dir_y;
		line_height = HEIGHT / perp_wall_dist;
		draw_start = HEIGHT/2 - line_height/2;
		draw_end   = HEIGHT/2 + line_height/2;
		if (ray.hit_side == 0)
			draw_vertical_line(cub, i, draw_start, draw_end, 0x00FFC0CB);
		else
			draw_vertical_line(cub, i, draw_start, draw_end, 0x00FF0000);
		i++;
	}
	return (0);
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
	render_fullmap(cub);
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}
