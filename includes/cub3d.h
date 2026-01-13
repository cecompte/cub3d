#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_game
{
	int	run;
	int	win_width;
	int	win_height;
}				t_game;

typedef struct s_map_info
{
	int		width;
	int		height;
}				t_map_info;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
}				t_texture;

typedef struct s_pos
{
	double			x; // pour raycasting(?)
	double			y;
	double			dir_x;
	double			dir_y;
	char			strt_dir;
}				t_pos;

typedef struct s_cub3d
{
	t_game		game;
	t_map_info	map_info;
	char		**map;
	t_texture	texture;
	t_pos		pos;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_cub3d;

int		check_map(char **arg);
int		extension_map(int ac, char **av);
char	**read_map(char av[1], t_cub3d *cub);
int		parce_config(char **map, t_cub3d *cub);
void	init_cub3d(t_cub3d *cub);


#endif
