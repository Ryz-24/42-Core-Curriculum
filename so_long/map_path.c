#include "so_long.h"

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->height)
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, width, height);
	flood_fill(map, x - 1, y, width, height);
	flood_fill(map, x, y + 1, width, height);
	flood_fill(map, x, y - 1, width, height);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}


void	check_path(t_game *game)
{
	char	**copy;
	int		i;
	int		j;

	copy = copy_map(game);
	if (!copy)
		error_msg(game, "Map copy failed\n");
	flood_fill(copy, game->player_x, game->player_y,
		game->width, game->height);
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (copy[i][j] == 'C' || copy[i][j] == 'E')
			{
				free_map(copy);
				error_msg(game, "Invalid path\n");
			}
			j++;
		}
		i++;
	}
	free_map(copy);
}
