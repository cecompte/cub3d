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

static int	load_one_texture(t_cub3d *cub, t_img *img, char *path)
int	**create_texture_table(t_img *img)
{
	int		**texture;
	char	*pixel_address;
	int		y;
	int		x;

	texture = malloc(img->height * sizeof(int *));
	if (!texture)
		return (NULL);
	y = 0;
	while (y < img->height)
	{
		texture[y] = malloc(img->width * sizeof(int));
		if (!texture[y])
			return (free_array(texture, y), NULL);
		x = 0;
		while (x < img->width)
        {
			pixel_address = img->addr + y * img->line_length + x * img->bits_per_pixel / 8;;
			texture[y][x] = *(int *)pixel_address;
			x++;
		}
		y++;
	}
	return (texture);
}

static void	load_one_texture(t_cub3d *cub, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &img->width, &img->height);
	if (!img->img)
	{
		ft_putstr_fd("Error\nCannot load texture\n", 2);
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
	img->texture_table = create_texture_table(img);
	if (!img->texture_table)
	{
		ft_putstr_fd("Error\nMalloc failed", 2);
		exit(1);
	}
}

int	load_texture(t_cub3d *cub)
{
	if (load_one_texture(cub, &cub->tex_n, cub->texture.no_path))
		return (1);
	if (load_one_texture(cub, &cub->tex_s, cub->texture.so_path))
		return (1);
	if (load_one_texture(cub, &cub->tex_w, cub->texture.we_path))
		return (1);
	if (load_one_texture(cub, &cub->tex_e, cub->texture.ea_path))
		return (1);
	return (0);
}
