#include "cub3d.h"

/*oid	init_game(t_cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height, "Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height);
	cub->img.img = mlx_new_image(cub->mlx_ptr, cub->game.win_width, cub->game.win_height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length,
								&cub->img.endian);
}*/

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close (fd);
	return (0);
}

int	validate_texture(t_cub3d *cub)
{
	if (check_extension(cub->texture.no_path, ".xpm")
		|| check_extension(cub->texture.so_path, ".xpm")
		|| check_extension(cub->texture.we_path, ".xpm")
		|| check_extension(cub->texture.ea_path, ".xpm"))
		return (ft_putstr_fd("Error\nTexture must be .xpm\n", 2), 1);
	if (check_file(cub->texture.no_path) || check_file(cub->texture.so_path)
		|| check_file(cub->texture.we_path) || check_file(cub->texture.ea_path))
		return (ft_putstr_fd("Error\nTexture file not found\n", 2), 1);
	return (0);
}

static void	load_one_texture(t_cub3d *cub, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &width, &height);
	if (!img->img)
	{
		ft_putstr_fd("Error\nCannot load texture\n", 2);
		exit (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	load_texture(t_cub3d *cub)
{
	load_one_texture(cub, &cub->tex_n, cub->texture.no_path);
	load_one_texture(cub, &cub->tex_s, cub->texture.so_path);
	load_one_texture(cub, &cub->tex_w, cub->texture.we_path);
	load_one_texture(cub, &cub->tex_e, cub->texture.ea_path);
}
