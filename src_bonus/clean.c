#include "cub3d_bonus.h"

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
		free(texture->no_path);
	if (texture->so_path)
		free(texture->so_path);
	if (texture->we_path)
		free(texture->we_path);
	if (texture->ea_path)
		free(texture->ea_path);
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
	if (cub->tex_e.texture_table)
		free_array(cub->tex_e.texture_table, cub->tex_e.height);
	if (cub->tex_s.texture_table)
		free_array(cub->tex_s.texture_table, cub->tex_s.height);
	if (cub->tex_w.texture_table)
		free_array(cub->tex_w.texture_table, cub->tex_w.height);
	if (cub->tex_n.texture_table)
		free_array(cub->tex_n.texture_table, cub->tex_n.height);
	if (cub->tex_door.texture_table)
		free_array(cub->tex_door.texture_table, cub->tex_door.height);
	return (1);
}

int	close_game(t_cub3d *cub)
{
	if (cub->tex_e.img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_e.img);
	if (cub->tex_n.img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_n.img);
	if (cub->tex_s.img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_s.img);
	if (cub->tex_w.img)
		mlx_destroy_image(cub->mlx_ptr, cub->tex_w.img);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx_ptr, cub->img.img);
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free_cub3d(cub);
	exit(0);
	return (0);
}
