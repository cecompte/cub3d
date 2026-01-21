#include "cub3d.h"


void	init_game(t_cub3d *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		exit(1);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->game.win_width,
			cub->game.win_height, "Cub3D");
	//cub->img_ptr = mlx_new_image(cub->mlx_ptr, cub->game.win_width,
	//		cub->game.win_height);// not used
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
	//if (!check_map(av[1]))
		//return (ft_putstr_fd("Error\nMap is not valid\n", 2), 1);
	if (check_extension(av[1], ".cub"))
		return (ft_putstr_fd("Error\nNot good extention of map\n", 2), 1);
	return (0);
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
	find_player_minimap(&cub); // ??? I have function find_player in map_grid.c but find_player_minimap(&cub) copy serch result to cub.player for minimap
	//maybe better to change find_player_minimap(&cub) for function d init_player_position(&cub) that will set cub.player.x and cub.player.y from cub.player_minimap
	/*cub->player.x += 0.5;
    cub->player.y += 0.5;

    if (cub->player.strt_dir == 'N')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = -1;
    }
    else if (cub->player.strt_dir == 'S')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = 1;
    }
    else if (cub->player.strt_dir == 'W')
    {
        cub->player.dir_x = -1;
        cub->player.dir_y = 0;
    }
    else if (cub->player.strt_dir == 'E')
    {
        cub->player.dir_x = 1;
        cub->player.dir_y = 0;
    }
    cub->player.plane_x = -0.66 * cub->player.dir_y;
    cub->player.plane_y = 0.66 * cub->player.dir_x;*/
	if (validate_texture(&cub))
		return (free_cub3d(&cub), 1);
	init_game(&cub);
	if (load_texture(&cub))
		return (free_cub3d(&cub), 1);
	/*Creating a 2D representation of the map (like a grid) and making player move & cast rays*/
	//parse_map_sl(&cub, av);

	init_minimap(&cub);
	mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &cub);
	mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &cub);
	mlx_hook(cub.win_ptr, DestroyNotify, StructureNotifyMask, &close_game, &cub);
	mlx_loop_hook(cub.mlx_ptr, render_frame, &cub);
	mlx_loop(cub.mlx_ptr);
	free_cub3d(&cub);
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
