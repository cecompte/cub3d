#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		pixel_offset;

	if (!img || !img->addr || x < 0 || y < 0)
		return ;
	pixel_offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + pixel_offset;
	*(unsigned int *)dst = color;
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	free_nodes(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	free_tabc(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_array(int **arr, int height)
{
	int	y;

	y = 0;
	if (!arr)
		return ;
	while (y < height)
	{
		free(arr[y]);
		y++;
	}
	free(arr);
}
