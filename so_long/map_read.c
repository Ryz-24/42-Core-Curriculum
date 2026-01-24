#include "so_long.h"

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

/* filled map + set height*/
void	read_map(t_game *game, char *file)
{
	int		fd;
	int		i;
	char	*line;

	game->height = count_lines(file);
	if (game->height <= 0)
		error_msg(game, "Invalid map\n");
	game->map = malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		error_msg(game, "Malloc failed\n");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg(game, "Failed to open map\n");
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		game->map[i] = ft_strtrim(line, "\n");
		if (!game->map[i])
			error_msg(game, "Malloc failed\n");
		free(line);
		i++;
	}
	game->map[i] = NULL;
	close(fd);
}
