#include "cub3d.h"

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

char	**get_texture_dest(char *line, t_texture *texture)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (&texture->no_path);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (&texture->so_path);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (&texture->we_path);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (&texture->ea_path);
	return (NULL);
}

static int	parse_rgb(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	parce_config(char **map, t_cub3d *cub)
{
	char	**dest;
	char	*line;
	int		*color_dest;
	int		i;

	i = 0;
	while (map[i])
	{
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
			break ;
		}
		i++;
	}
	if (!config_complete(&cub->texture))
		return (ft_putstr_fd("Error\nIncomplete config\n", 2), 1);
	return (0);
}

