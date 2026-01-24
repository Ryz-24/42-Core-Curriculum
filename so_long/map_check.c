#include "so_long.h"

static void	check_rectangle(t_game *game)
{
	int	i;
	int	len;

	if (!game->map || !game->map[0])
		error_msg(game, "Map is empty\n");
	i = 0;
	len = ft_strlen(game->map[0]);
	game->width = len;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != len)
			error_msg(game, "Map is not rectangular\n");
		i++;
	}
}

static void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if ((i == 0 || i == game->height - 1
					|| j == 0 || j == game->width - 1)
				&& game->map[i][j] != '1')
				error_msg(game, "Map is not surrounded by walls\n");
			j++;
		}
		i++;
	}
}

static void	check_chars(t_game *game)
{
	int	i;
	int	j;
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	game->collectible = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] == 'P')
			{
				p_count++;
				game->player_x = j;
				game->player_y = i;
			}
			else if (game->map[i][j] == 'E')
				e_count++;
			else if (game->map[i][j] == 'C')
				game->collectible++;
			else if (game->map[i][j] != '0' && game->map[i][j] != '1')
				error_msg(game, "Invalid character in map\n");
			j++;
		}
		i++;
	}
	if (p_count != 1 || e_count != 1 || game->collectible < 1)
		error_msg(game, "Invalid number of P, E, or C\n");
}

void	validate_map(t_game *game)
{
	check_rectangle(game);
	check_walls(game);
	check_chars(game);
}
