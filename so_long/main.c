#include "so_long.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;

	game->map = NULL;
	game->width = 0;
	game->height = 0;

	game->player_x = 0;
	game->player_y = 0;

	game->collectible = 0;
	game->moves = 0;

	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_exit = NULL;
	game->img_collectible = NULL;
}

int	handle_expose(t_game *game)
{
	render_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_msg(NULL, "Invalid number of arguments\n");

	init_game(&game);

	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		error_msg(&game, "Invalid map extension\n");
	read_map(&game, argv[1]);

	validate_map(&game);
	check_path(&game);

	init_mlx(&game);
	load_images(&game);
	render_map(&game);

	mlx_key_hook(game.win, handle_key, &game);
	mlx_expose_hook(game.win, handle_expose, &game);
	mlx_hook(game.win, 17, 0, clean_exit, &game);

	mlx_loop(game.mlx);
	return (0);
}

