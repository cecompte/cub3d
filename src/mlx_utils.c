#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	render_frame(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (cub->img.img)
		mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
	return (0);
}

