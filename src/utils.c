/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:30 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/03 15:25:11 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	return (0);
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
