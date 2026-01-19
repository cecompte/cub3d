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
				|| map[i][j] == ' ' || map[i][j] == '\n')
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

static char	**make_rect_map(char **map, int height, int width)
{
	int		i;
	int		j;
	char	**rect_map;

	i = 0;
	rect_map = malloc(sizeof(char *) * (height + 1));
	if (!rect_map)
		return (NULL);
	while (i < height)
	{
		rect_map[i] = malloc(sizeof(char) * (width + 1));
		if (!rect_map[i])
			return (free_tabc(rect_map), NULL);
		j = 0;
		while (map[i][j])
		{
			rect_map[i][j] = map[i][j];
			j++;
		}
		while (j < width)
			rect_map[i][j++] = ' ';
		rect_map[i][j] = '\0';
		i++;
	}
	rect_map[i] = NULL;
	return (rect_map);
}

static void	restore_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	parce_map_grid(char **map, t_cub3d *cub)
{
	char	**rect_map;

	cub->map_info.height = get_map_height(map);
	cub->map_info.width = get_max_width(map, cub->map_info.height);
	if (check_empty_line(map))
		return (ft_putstr_fd("Error\nEmpty line in map\n", 2), 1);
	if (find_player(map, &cub->player) != 0)
		return (1);
	if (check_chars(map) != 0)
		return (ft_putstr_fd("Error\nInvalid character in map\n", 2), 1);
	rect_map = make_rect_map(map, cub->map_info.height, cub->map_info.width);
	if (!rect_map)
		return (ft_putstr_fd("Error\nWall is not closed\n", 2), 1);
	if (flood_fill(rect_map, &cub->map_info, (int)cub->player.y,
			(int)cub->player.x) != 0)
	{
		free_tabc(rect_map);
		return (ft_putstr_fd("Error\nWall is not closed\n", 2), 1);
	}
	restore_map(rect_map);
	cub->map_grid = rect_map;
	return (0);
}
