/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:26:46 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/17 15:26:51 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Multiplying by TILE_SIZE converts tiles → pixels */
#define TILE_SIZE 32

/* starts MLX and opens a window that’s the right size 
    for the map so the game can be drawn on screen */
void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_msg("mlx_init failed\n");
	game->win = mlx_new_window(
			game->mlx,
			game->width * TILE_SIZE,
			game->height * TILE_SIZE,
			"so_long");
	if (!game->win)
		error_msg("mlx_new_window failed\n");
}

/* loads all the XPM files once and stores the MLX image pointers 
    inside t_game so they can be reused during rendering */
void	load_images(t_game *game)
{
	int	w;
	int	h;

	game->img_wall = mlx_xpm_file_to_image(
			game->mlx, "textures/wall.xpm", &w, &h);
	game->img_floor = mlx_xpm_file_to_image(
			game->mlx, "textures/floor.xpm", &w, &h);
	game->img_player = mlx_xpm_file_to_image(
			game->mlx, "textures/player.xpm", &w, &h);
	game->img_exit = mlx_xpm_file_to_image(
			game->mlx, "textures/exit.xpm", &w, &h);
	game->img_collectible = mlx_xpm_file_to_image(
			game->mlx, "textures/collectible.xpm", &w, &h);
	if (!game->img_wall || !game->img_floor
		|| !game->img_player || !game->img_exit
		|| !game->img_collectible)
		error_msg("Failed to load images\n");
}

static void	render_map_helper(t_game *game, char tile, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_floor,
		x * TILE_SIZE, y * TILE_SIZE);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_player, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
}

/* goes through every tile in the map and draws the correct
    images to the window, making sure the floor is always
    drawn first so other tiles appear on top */
void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			render_map_helper(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
