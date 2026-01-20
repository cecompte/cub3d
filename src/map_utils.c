#include "cub3d.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_max_width(char **map, int height)
{
	int	max;
	int	len;
	int	i;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = (int)ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	check_empty_line(char **map)
{
	int	i;
	int	map_end;

	i = 0;
	map_end = 0;
	while (map[i] && map[i][0] == '\0')
		i++;
	while (map[i])
	{
		if (map[i][0] == '\0' || map[i][0] == '\n' || map[i][1] == '\0')
			map_end = 1;
		else if (map_end == 1)
			return (1);
		i++;
	}
	return (0);
}

int	flood_fill(char **map, t_map_info *info, int y, int x)
{
	if (y < 0 || y >= info->height || x < 0 || x >= info->width)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (flood_fill(map, info, y + 1, x) || flood_fill(map, info, y - 1, x)
		|| flood_fill(map, info, y, x + 1) || flood_fill(map, info, y, x - 1))
		return (1);
	return (0);
}
