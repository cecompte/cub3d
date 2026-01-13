#include "cub3d.h"

static void	save_player(t_pos *pos, int i, int j, char dir)
{
	pos->strt_dir = dir;
	pos->x = j;
	pos->y = i;
}

int	find_player(char **map, t_pos *pos)
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
				save_player(pos, i, j, map[i][j]);
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

int	check_chars(char **map)
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
				|| map[i][j] == 'W' || map[i][j] == '1' || map[i][j] == '0'
				|| map[i][j] == ' ')
				j++;
			else
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}
/*-Первый и последний символ строки обязаны быть '1',
иначе карта считается «протекающей» (незакрытой).

-Если текущая строка длиннее строки сверху:
Тогда все «выступающие» символы справа (те, у которых current_col > strlen(row_on_top)) должны быть '1'.
→ Это нужно, чтобы не возникало "дыр" между строками разной длины.

-Если текущая строка длиннее строки снизу:
То же самое правило — все символы правее длины нижней строки должны быть '1'.
*/

int	check_bot_wall(char **map, int i, int len_cur)
{
	int	j;
	int	len_bot;

	len_bot = ft_strlen(map[i + 1]);
	if (len_cur > len_bot)
	{
		j = len_bot;
		while (j < len_cur)
		{
			if (map[i][j] != '1')
				return (1);
			j++;
		}
	}
	return (0);
}

int	check_top_wall(char **map, int i, int len_cur)
{
	int	j;
	int	len_top;

	len_top = ft_strlen(map[i - 1]);
	if (len_cur > len_top)
	{
		j = len_top;
		while (j < len_cur)
		{
			if (map[i][j] != '1')
				return (1);
			j++;
		}
	}
	return (0);
}


int	check_walls(char **map)
{
	int	i;
	int	len_cur;

	i = 0;
	while (map[i])
	{
		len_cur = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][len_cur - 1] != '1')
			return (1);
		if (i > 0)
		{
			if (check_top_wall(map, i, len_cur))
				return (1);
		}
		if (map[i + 1])
		{
			if (check_bot_wall(map, i, len_cur))
				return (1);
		}
		i++;
	}
	return (0);
}

int	parce_map_grid(char **map, t_cub3d *cub)
{
	if (find_player(map, &cub->pos) == 0)
		return (0);


	cub->map_grid = map; //start of map_grid assignment
	if (check_chars(map) != 0)
		return (ft_putstr_fd("Error\nInvalid character in map\n", 2), 1);
	if (check_walls(map) != 0)
		return (ft_putstr_fd("Error\nWall is not close\n", 2), 1);

	/*cub->map_grid = map;
	return (1);
	//check_chars
	8f97436ce3df45eb764e7df206a0ef0441e67b13*/
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
