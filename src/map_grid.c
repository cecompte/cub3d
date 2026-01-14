#include "cub3d.h"

static void	save_player(t_player *player, int i, int j, char dir)
{
	player->strt_dir = dir;
	player->x = j;
	player->y = i;
}

int	find_player(char **map, t_player *player)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	j = 0;
	i = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W' )
			{
				save_player(player, i, j, map[i][j]);
				player_count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error\nNo player found in map\n", 2), 1);
	return (0);
}


int	parce_map_grid(char **map, t_cub3d *cub)
{
	if (find_player(map, &cub->player) == 0)
		return (0);

	cub->map_grid = map;
	return (1);
	//check_chars
	//flood_fill
	/*char	**grid;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			grid[i][j] = map[i][j];
			j++;
		}
		j = 0;
		i++;
	}*/

}
