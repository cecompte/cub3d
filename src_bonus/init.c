/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:43 by cecompte          #+#    #+#             */
/*   Updated: 2026/02/04 16:39:05 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_texture_and_player(t_texture *texture, t_player *player)
{
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->floor_color = -1;
	texture->ceiling_color = -1;
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->strt_dir = 0;
}

static void	init_win(t_game *game)
{
	game->run = 1;
	game->win_width = 1024;
	game->win_height = 768;
	game->move_speed = 3;
	game->rotation_angle = 1.5;
	game->last_frame_time = get_current_time();
	game->mouse_enabled = 1;
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

static void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
	img->texture_table = NULL;
}

void	init_cub3d(t_cub3d *cub)
{
	init_win(&cub->game);
	init_texture_and_player(&cub->texture, &cub->player);
	init_input(&cub->input);
	init_img(&cub->tex_e);
	init_img(&cub->tex_n);
	init_img(&cub->tex_s);
	init_img(&cub->tex_w);
	init_img(&cub->tex_door);
	init_img(&cub->img);
	init_minimap(cub);
	cub->map_info.width = 0;
	cub->map_info.height = 0;
	cub->map = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->map_grid = NULL;
	cub->minimap.offset_x = 10;
	cub->minimap.offset_y = 10;
	cub->minimap.tile_size = 8;
	cub->minimap.width = 0;
	cub->minimap.height = 0;
	cub->doors = NULL;
	cub->door_index = NULL;
	cub->door_count = 0;
}
