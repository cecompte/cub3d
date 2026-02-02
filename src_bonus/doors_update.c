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
