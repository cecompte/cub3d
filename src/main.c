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
	if (parce_config(cub.map, &cub))
		return (1);
	if (validate_texture(&cub))
		return (1);
	/*Creating a 2D representation of the map (like a grid) and making player move & cast rays*/
	//parse_map_sl(&cub, av);

	init_minimap(&cub);
	init_game(&cub);
	mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &cub);
	mlx_hook(cub.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &cub);
	mlx_hook(cub.win_ptr, DestroyNotify, StructureNotifyMask, &close_game, &cub);
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
