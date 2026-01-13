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

static void	init_pos(t_pos *pos)
{
	pos->x = 0;
	pos->y = 0;
	pos->dir_x = 0;
	pos->dir_y = 0;
	pos->strt_dir = 0;
}

static void	init_win(t_game *game)
{
	game->run = 1;			// Game loop flag: 1 = running, 0 = exit
	game->win_width = 800;	// Default window width in pixels (4:3 aspect)
	game->win_height = 600;	// Default window height in pixels
}

void	init_cub3d(t_cub3d *cub)
{
	init_win(&cub->game);
	init_texture(&cub->texture);
	init_pos(&cub->pos);
	cub->map_info.width = 0;
	cub->map_info.height = 0;
	cub->map = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
}
