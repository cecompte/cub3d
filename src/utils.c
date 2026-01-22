#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		pixel_offset;

	if (!img || !img->addr || x < 0 || y < 0)
		return;
	pixel_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + pixel_offset;
	*(unsigned int*)dst = color;
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
