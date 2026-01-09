/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:09:27 by cecompte          #+#    #+#             */
/*   Updated: 2026/01/09 14:10:09 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    /*
    =========================================================
    1. CHECK ARGUMENTS
    ---------------------------------------------------------
    - Must have exactly 2 arguments (program + map.cub)
    - Check file extension is ".cub"
    =========================================================
    */

    /*
    =========================================================
    2. INITIALIZE MAIN STRUCTURES
    ---------------------------------------------------------
    - Create main game struct
    - Set default values (NULL pointers, flags, etc.)
    =========================================================
    */

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
