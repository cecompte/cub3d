/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:42:13 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:42:18 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_islands(char **map, t_map_info info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info.height)
	{
		j = 0;
		while (j < info.width)
		{
			if (map[i][j] == '0')
			{
				if (flood_fill(map, &info, i, j) != 0)
				{
					return (ft_putstr_fd("Error\nWall is not closed\n", 2), 1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
