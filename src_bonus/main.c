/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/03 20:42:34 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_game(t_cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		exit(1);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height, "Cub3D");
	if (!cub->win_ptr)
	{
		free_cub3d(cub);
		exit(1);
	}
	cub->img.img = mlx_new_image(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
}

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	if (check_extension(av[1], ".cub"))
		return (ft_putstr_fd("Error\nNot good extention of map\n", 2), 1);
	return (0);
}

void	hooks(t_cub3d *cub)
{
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, cub);
	mlx_hook(cub->win_ptr, DestroyNotify, StructureNotifyMask,
		&close_game, cub);
	mlx_mouse_hide(cub->mlx_ptr, cub->win_ptr);
	mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, cub->game.win_width / 2,
		cub->game.win_height / 2);
	mlx_hook(cub->win_ptr, 6, 1L << 6, &handle_mouse, cub);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	init_cub3d(&cub);
	if (check_arguments(ac, av))
		return (1);
	cub.map = read_map(av[1], &cub);
	if (!cub.map)
		return (1);
	if (parce_config(cub.map, &cub))
		return (free_cub3d(&cub), 1);
	if (init_all_doors(&cub))
		return (free_cub3d(&cub), 1);
	if (validate_texture(&cub))
		return (free_cub3d(&cub), 1);
	init_game(&cub);
	if (load_texture(&cub))
		return (free_cub3d(&cub), 1);
	hooks(&cub);
	mlx_loop_hook(cub.mlx_ptr, render_frame, &cub);
	mlx_loop(cub.mlx_ptr);
	free_cub3d(&cub);
	return (0);
}
