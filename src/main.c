/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:09:27 by cecompte          #+#    #+#             */
/*   Updated: 2026/01/13 12:56:35 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
=========================================================
1. CHECK ARGUMENTS
---------------------------------------------------------
- Must have exactly 2 arguments (program + map.cub)
- Check file extension is ".cub"
=========================================================
*/
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

	/*
	=========================================================
	2. INITIALIZE MAIN STRUCTURES
	---------------------------------------------------------
	- Create main game struct
	- Set default values (NULL pointers, flags, etc.)
	=========================================================
	*/
	init_cub3d(&cub);
	if (check_arguments(ac, av))
		return (1);

	/*
	=========================================================
	3. PARSE .CUB FILE
	---------------------------------------------------------
	- Open file
	- Read line by line
	- Parse:
		* texture paths (NO, SO, WE, EA)
		* floor color (F)
		* ceiling color (C)
	- Then read the map lines
	- Store everything in structures
	=========================================================
	*/
	cub.map = read_map(av[1], &cub);

	/*
	=========================================================
	4. VALIDATE PARSED DATA
	---------------------------------------------------------
	- Check all textures exist and are accessible
	- Check colors are valid RGB values (0-255)
	- Check map:
		* only valid characters
		* exactly one player (N/S/E/W)
		* map is closed (walls around)
	=========================================================
	*/
	if (parce_config(cub.map, &cub))
		return (1);

	/*
	=========================================================
	5. INITIALIZE PLAYER
	---------------------------------------------------------
	- Find player position in map
	- Convert map coords to float world coords
	- Set direction vector from N/S/E/W
	- Set camera plane (for FOV)
	=========================================================
	*/

	/*
	=========================================================
	6. INIT MLX AND WINDOW
	---------------------------------------------------------
	- mlx_init()
	- mlx_new_window()
	- mlx_new_image() for main frame buffer
	- get image data address
	=========================================================
	*/

	/*
	=========================================================
	7. LOAD TEXTURES
	---------------------------------------------------------
	- For each texture path:
		* mlx_xpm_file_to_image()
		* get texture pixel data
	=========================================================
	*/

	/*
	=========================================================
	8. SET HOOKS (EVENTS)
	---------------------------------------------------------
	- Key press hook
	- Key release hook (if needed)
	- Window close hook
	- Loop hook for rendering
	=========================================================
	*/

	/*
	=========================================================
	9. MAIN LOOP
	---------------------------------------------------------
	- mlx_loop()
	- Rendering will be called repeatedly from loop hook
	=========================================================
	*/

	/*
	=========================================================
	10. CLEAN EXIT (if loop ever ends)
	---------------------------------------------------------
	- Destroy images
	- Destroy window
	- Free all allocated memory
	=========================================================
	*/

	return (0);
}
/*
Notes discussion avec Ben
- mlx hook pour affichage en continu ( pas mlx key hook )
- structure map en blocks
- fonction my mlx image pour modifier l'adresse de l'image et changer le pixel en question
- commencer par faire une minimap en 2d, afficher le joueur et les rayons et voir si ca marche

*/