/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <esergeev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 19:44:04 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			pixel_address = img->addr + y * img->line_length + x
				* img->bits_per_pixel / 8;
			texture[y][x] = *(int *)pixel_address;
			x++;
		}
		y++;
	}
	return (texture);
}

static int	load_one_texture(t_cub3d *cub, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img)
	{
		close_game(cub);
		ft_putstr_fd("Error\nCannot load texture\n", 2);
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->texture_table = create_texture_table(img);
	if (!img->texture_table)
	{
		close_game(cub);
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	return (0);
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
	if (load_one_texture(cub, &cub->tex_door, "./texture/wooden-door.xpm"))
		return (1);
	return (0);
}
