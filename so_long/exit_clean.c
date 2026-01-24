#include "so_long.h"

static void	destroy_game(t_game *game)
{
	if (!game)
		return ;

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

	free_map(game->map);
}

int clean_exit(t_game *game)
{
	destroy_game(game);
	exit(0);
}

void	error_msg(t_game *game, char *msg)
{
	if (msg)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen(msg));
	}
	destroy_game(game);
	exit(1);
}
