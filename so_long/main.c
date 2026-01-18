/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:24:23 by rzaatreh          #+#    #+#             */
/*   Updated: 2026/01/17 15:24:40 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean_exit(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->mlx && game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	error_msg(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->moves = 0;
	game->collectible = 0;
}

int	main(int argc, char **argv)
{
	int		len;
	t_game	game;

	if (argc != 2)
		error_msg("Invalid number of arguments\n");
	init_game(&game);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
		error_msg("Invalid map extension\n");
	read_map(&game, argv[1]);
	validate_map(&game);
	check_path(&game);
	init_mlx(&game);
	load_images(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, clean_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
