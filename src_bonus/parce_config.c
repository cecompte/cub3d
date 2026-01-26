#include "cub3d_bonus.h"

int	config_complete(t_texture *texture)
{
	return (texture->no_path && texture->so_path && texture->ea_path
		&& texture->we_path && (texture->floor_color != -1)
		&& (texture->ceiling_color != -1));
}

int	*get_color_dest(char *line, t_texture *texture)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (&texture->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (&texture->ceiling_color);
	return (NULL);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (-1);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_tabc(rgb), -1);
	if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
	{
		free_tabc(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_tabc(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	handle_parce_config(char **map, t_cub3d *cub, int i)
{
	char	**dest;
	char	*line;
	int		*color_dest;

	line = map[i];
	while (*line == ' ' || *line == '\n' || *line == '\t')
		line++;
	dest = get_texture_dest(line, &cub->texture);
	color_dest = get_color_dest(line, &cub->texture);
	if (dest && *dest)
		return (ft_putstr_fd("Error\nDuplicate texture\n", 2), 1);
	else if (dest)
		*dest = ft_strtrim(line + 3, " \t\n");
	else if (color_dest && *color_dest != -1)
		return (ft_putstr_fd("Error\nDuplicate color\n", 2), 1);
	else if (color_dest)
		*color_dest = parse_rgb(line + 2);
	else if (*line == '1' || *line == '0')
	{
		if (parce_map_grid(&map[i], cub))
			return (1);
		return (2);
	}
	return (0);
}

int	parce_config(char **map, t_cub3d *cub)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (map[i])
	{
		res = handle_parce_config(map, cub, i);
		i++;
		if (res == 1)
			return (1);
		else if (res == 2)
			break ;
	}
	if (!config_complete(&cub->texture))
		return (ft_putstr_fd("Error\nIncomplete config\n", 2), 1);
	return (0);
}

