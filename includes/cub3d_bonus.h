/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:30 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:14:11 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <sys/time.h>

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define E_KEY 101
# define SPACE_KEY 32
# define OPEN 1
# define OPENING 2
# define CLOSING 3
# define CLOSED 0
# define VERTICAL -1
# define HORIZONTAL -2

typedef struct s_game
{
	int			run;
	int			win_width;
	int			win_height;
	double		rotation_angle;
	double		move_speed;
	size_t		last_frame_time;
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
	double		camera_x;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit_side;
	double		line_height;
	double		perp_wall_dist;
	double		draw_start;
	double		draw_end;
	double		wall_x;
	int			tex_x;
}				t_ray;

typedef struct s_input
{
	int			up;
	int			left;
	int			right;
	int			down;
	int			rotate_left;
	int			rotate_right;
}				t_input;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			**texture_table;
}				t_img;

typedef struct s_minimap
{
	int			offset_x;
	int			offset_y;
	int			tile_size;
	int			width;
	int			height;
}				t_minimap;

typedef struct s_door
{
	int			map_x;
	int			map_y;
	int			state;
	double		openness;
	double		opening_speed;
	int			direction;
}				t_door;

typedef struct s_cub3d
{
	t_game		game;
	t_map_info	map_info;
	char		**map;
	t_texture	texture;
	t_img		tex_n;
	t_img		tex_s;
	t_img		tex_w;
	t_img		tex_e;
	t_player	player;
	t_input		input;
	t_img		img;
	t_minimap	minimap;
	t_img		tex_door;
	t_door		*doors;
	int			**door_index;
	int			door_count;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map_grid;
}				t_cub3d;

int		check_extension(char *str, char *ext);
char	**read_map(char av[1], t_cub3d *cub);
int		parce_config(char **map, t_cub3d *cub);
int		parce_map_grid(char **map, t_cub3d *cub);
void	init_cub3d(t_cub3d *cub);
int		get_map_height(char **map);
int		get_max_width(char **map, int height);
int		flood_fill(char **map, t_map_info *info, int y, int x);
int		check_empty_line(char **map);
int		check_file(char *path);
int		validate_texture(t_cub3d *cub);
int		load_texture(t_cub3d *cub);
char	**get_texture_dest(char *line, t_texture *texture);
int		check_chars(char **map);
int		check_islands(char **map, t_map_info info);

//clean
int		free_cub3d(t_cub3d *cub);
void	free_texture(t_texture *texture);
int		close_game(t_cub3d *cub);
void	free_tabc(char **tab);

// utils
size_t	get_current_time(void);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	free_nodes(t_list *list);
void	free_array(int **arr, int height);
void	rotate(t_cub3d *cub, double angle);
void	clamp_values(int *val, int size);

// minimap
void	init_minimap(t_cub3d *cub);
int		render_minimap(t_cub3d *cub);
int		draw_player_minimap(t_cub3d *cub);
void	draw_segment(t_cub3d *cub, double start[], double end[], int color);

// full map
int		render_frame(void *param);
void	init_game(t_cub3d *cub);
void	init_ray(t_cub3d *cub, t_ray *ray);
int		dda_loop(t_cub3d *cub, t_ray *ray);
void	calc_draw_values(t_cub3d *cub, t_ray *ray);
void	draw_textured_line(t_cub3d *cub, t_ray *ray, t_img *img, int col);

// movements
void	handle_inputs(t_cub3d *cub, double delta_time);
int		handle_keypress(int keycode, t_cub3d *cub);
int		handle_keyrelease(int keycode, t_cub3d *cub);
int		handle_mouse(int x, int y, t_cub3d *cub);

//doors
int		count_doors(char **map);
int		init_all_doors(t_cub3d *cub);
void	door_update(t_cub3d *cub, double delta_time);
void	draw_door(t_cub3d *cub, t_ray *ray, int col);
int		can_pass_door(t_cub3d *cub, int x, int y);
void	toggle_door(t_cub3d *cub);

#endif
