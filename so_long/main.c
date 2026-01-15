#include "so_long.h"

int	clean_exit(t_game *game)
{
	if (game->map)
		free_map(game->map);

	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
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
	t_game	game;

	if (argc != 2)
		error_msg("Invalid number of arguments\n");

	init_game(&game);

	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
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

