#include "cub3d.h"

static void	init_texture(t_texture *texture)
{
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->floor_color = -1;
	texture->ceiling_color = -1;
}

static void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->strt_dir = 0;
}

static void	init_win(t_game *game)
{
	game->run = 1;			// Game loop flag: 1 = running, 0 = exit
	game->win_width = 1024;	// Default window width in pixels (4:3 aspect)
	game->win_height = 768;	// Default window height in pixels
	game->move_speed = 3;
	game->rotation_speed = 1.5;
	game->last_frame_time = get_current_time();
}

static void	init_input(t_input *input)
{
	input->down = 0;
	input->up = 0;
	input->left = 0;
	input->right = 0;
	input->rotate_left = 0;
	input->rotate_right = 0;
}

void	init_cub3d(t_cub3d *cub)
{
	init_win(&cub->game);
	init_texture(&cub->texture);
	init_player(&cub->player);
	init_input(&cub->input);
	cub->map_info.width = 0;
	cub->map_info.height = 0;
	cub->map = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->map_grid = NULL;
	cub->img.img = NULL;
	cub->img.addr = NULL;
	cub->minimap.offset_x = 10;
	cub->minimap.offset_y = 10;
	cub->minimap.tile_size = 8;
	cub->minimap.width = 0;
	cub->minimap.height = 0;
}
