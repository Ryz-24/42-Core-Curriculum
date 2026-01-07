#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include "mlx.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	
	char	**map;
	int	width;
	int	height;
	
	int	player_x;
	int	player_y;
	
	int	collectible;
	int	moves;

	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;

}	t_game;


void	error_msg(char *msg);

void	validate_map(t_game *game);


#endif
