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
	double		speed;
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
	double		plane_x;
	double		plane_y;
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
	double		cameraX;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit_side; // 0 = vertical, 1 = horizontal
	double		line_height;
	double		perp_wall_dist;
	double		draw_start;
	double		draw_end;
	double 		wallX; // where exactly the wall was hit (between 0 and 1)
	int			tex_x; // x coordinate on the texture
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
	int			width;
	int			height;
	int			**texture_table;
}				t_img;

typedef struct	s_minimap {
	int			offset_x;       // top-left corner of minimap in window
    int 		offset_y;
    int 		tile_size;      // size of each map square in pixels on minimap
    int 		width;          // total width in pixels
    int 		height;         // total height in pixels
} t_minimap;

typedef struct s_cub3d
{
	t_game		game;
	t_map_info	map_info;
	char		**map;
	t_texture	texture;
	t_img		tex_n;	//images
	t_img		tex_s;
	t_img		tex_w;
	t_img		tex_e;
	t_player	player;
	t_input		input;
	t_img		img;
	t_minimap	minimap;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		**map_grid;
	int			screen_width;
	int			screen_height;
}				t_cub3d;

int		check_extension(char *str, char *ext);
char	**read_map(char av[1], t_cub3d *cub);
int		parce_config(char **map, t_cub3d *cub);
int		parce_map_grid(char **map, t_cub3d *cub);
void	init_cub3d(t_cub3d *cub);
int		get_map_height(char **map);
int		get_max_width(char **map, int height);
int		flood_fill(char **map, t_map_info *info, int y, int x);
void	free_tabc(char **tab);
int		check_empty_line(char **map);
int		check_file(char *path);
int		validate_texture(t_cub3d *cub);
void	load_texture(t_cub3d *cub);
char	**get_texture_dest(char *line, t_texture *texture);
int		free_cub3d(t_cub3d *cub);
void	free_texture(t_texture *texture);



void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		render_frame(void *param);
void	init_game(t_cub3d *cub);

// minimap
int		parse_map_sl(t_cub3d *cub, char **argv);
void	init_minimap(t_cub3d *cub);
int		render_minimap(t_cub3d *cub);
int		find_player_minimap(t_cub3d *cub);
int		draw_player_minimap(t_cub3d *cub);
void	draw_segment(t_cub3d *cub, double x0, double y0, double x1, double y1, int color);

// full map
void	init_ray(t_cub3d *cub, t_ray *ray);
int		dda_loop(t_cub3d *cub, t_ray *ray);
void	draw_rays_utils(t_cub3d *cub, t_ray *ray);

// hooks
void	rotate(t_cub3d *cub, double angle);
void	update_position(t_cub3d *cub, int forward, int strafe, double speed);
int		handle_keypress(int keysym, t_cub3d *cub);
int		handle_keyrelease(int keysym, t_cub3d *cub);
int		close_game(t_cub3d *cub);
#endif
