/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:09:27 by cecompte          #+#    #+#             */
/*   Updated: 2026/01/13 15:28:35 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arguments(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	//if (!check_map(av[1]))
		//return (ft_putstr_fd("Error\nMap is not valid\n", 2), 1);
	if (extension_map(ac, av))
		return (ft_putstr_fd("Error\nNot good extention of map\n", 2), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	init_cub3d(&cub);
	if (check_arguments(ac, av))
		return (1);
	// cub.map = read_map(av[1], &cub);
	parse_map_sl(&cub, av);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.game.win_width, cub.game.win_height, "cub3d");
	draw_minimap(&cub);
	mlx_loop_hook(cub.mlx_ptr, render_frame, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
/*
Notes discussion avec Ben
- mlx hook pour affichage en continu ( pas mlx key hook )
- structure map en blocks
- fonction my mlx image pour modifier l'adresse de l'image et changer le pixel en question
- commencer par faire une minimap en 2d, afficher le joueur et les rayons et voir si ca marche
- structure vector
- structure color
*/