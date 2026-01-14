#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_game
{
	int			run;
	int			win_width;
	int			win_height;
}				t_game;

typedef struct s_map_info
{
	int			width;
	int			height;
}				t_map_info;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	char		strt_dir;
}				t_player;

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit_side; // 0 = vertical, 1 = horizontal
}				t_ray;

typedef struct s_input
{
	int			up;
	int			left;
	int			right;
	int			down;
	int			rotate_left;
	int			rotate_right;
} t_input;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_cub3d
{
	t_game		game;
	t_map_info	map_info;
	char		**map;
	t_texture	texture;
	t_player	player;
	t_ray		*ray;
	t_input		input;
	t_img		img;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		**map_grid;
	int			tile_size;
}				t_cub3d;

int		check_map(char **arg);
int		extension_map(int ac, char **av);
char	**read_map(char av[1], t_cub3d *cub);
int		parce_config(char **map, t_cub3d *cub);
int		parce_map_grid(char **map, t_cub3d *cub);
void	init_cub3d(t_cub3d *cub);
int		get_map_height(char **map);
int		get_max_width(char **map, int height);
int		flood_fill(char **map, t_map_info *info, int y, int x);
void	free_tabc(char **tab);



void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		render_frame(void *param);
void	init_game(t_cub3d *cub);

// minimap
int		parse_map_sl(t_cub3d *cub, char **argv);
int		init_minimap(t_cub3d *cub);
int		render_minimap(t_cub3d *cub);
int		find_player_minimap(t_cub3d *cub);
int		draw_player(t_cub3d *cub);
int 	draw_ray_fixed_step(t_cub3d *cub);
int		draw_ray_dda(t_cub3d *cub);

int		handle_keypress(int keysym, t_cub3d *cub);
int		handle_keyrelease(int keysym, t_cub3d *cub);
int		close_game(t_cub3d *cub);
#endif
