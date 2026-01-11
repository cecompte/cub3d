#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_game
{
	int

}				t_game;

typedef struct s_map
{

}				t_map;

typedef struct s_texture
{

}				t_texture;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_cub3d
{
	t_game		game;
	t_map		**map;
	t_texture	texture;
	t_pos		pos;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_cub3d;

int		check_map(char *arg);
int		extension_map(int ac, char **av);
char	**read_map(char av[1], t_cub3d *cub);

#endif
