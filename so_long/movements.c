#include "so_long.h"

static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;

	if (new_x < 0 || new_y < 0
		|| new_x >= game->width || new_y >= game->height)
		return ;

	if (game->map[new_y][new_x] == '1')
		return ;

	if (game->map[new_y][new_x] == 'C')
		game->collectible--;

	if (game->map[new_y][new_x] == 'E' && game->collectible != 0)
		return ;

	game->moves++;
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);

	if (game->map[new_y][new_x] == 'E' && game->collectible == 0)
		clean_exit(game);

	if (game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';

	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;

	render_map(game);
}


int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	return (0);
}
