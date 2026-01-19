#include "cub3d.h"

void	free_tabc(char **tab)
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
}

void	free_texture(t_texture *texture)
{
	if (texture->no_path)
		free (texture->no_path);
	if (texture->so_path)
		free (texture->so_path);
	if (texture->we_path)
		free (texture->we_path);
	if (texture->ea_path)
		free (texture->ea_path);
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
}

int	free_cub3d(t_cub3d *cub)
{
	if (cub->map)
		free_tabc(cub->map);
	free_texture(&cub->texture);
	if (cub->map_grid)
		free_tabc(cub->map_grid);
	return (1);
}
