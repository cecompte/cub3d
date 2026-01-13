#include "cub3d.h"

void	free_tab(char **tab)
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
	tab = NULL;
}

static int	count_lines(char **argv)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		i++;
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int parse_map_sl(t_cub3d *cub, char **argv)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(argv[1], O_RDONLY);
	cub->map = ft_calloc((count_lines(argv) + 1), sizeof(char *));
	if (!cub->map)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		cub->map[i] = ft_strtrim(line, "\n");
		if (!cub->map[i])
			return (free(line), free_tab(cub->map), 0);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free (line);
	cub->map[i] = 0;
	cub->map_info.height = count_lines(argv);
	cub->map_info.width = ft_strlen(cub->map[0]);
	close(fd);
	return (1);
}