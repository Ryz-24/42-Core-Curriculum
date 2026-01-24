#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include "minilibx-linux/mlx.h"

# define KEY_ESC 65307

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_game
{
	void	*mlx; //pointer to the MiniLibX context
	void	*win; //pointer to the game window
	
	char	**map; //the characters representing the map
	int	width; //number of columns in the map
	int	height; //number of the rows
	
	int	player_x; //player's column index
	int	player_y; //player's row index
	
	int	collectible;
	int	moves;

	/* Each pointer holds an MLX image */
	void	*img_wall; // '1'
	void	*img_floor; // '0'
	void	*img_player; // 'P'
	void	*img_exit; // 'E'
	void	*img_collectible; //'C'

}	t_game;


void	error_msg(t_game *game, char *msg);
int	handle_expose(t_game *game);

void	validate_map(t_game *game);
void	check_path(t_game *game);

void	read_map(t_game *game, char *file);

void	render_map(t_game *game);
int	handle_key(int keycode, t_game *game);
void	load_images(t_game *game);
void	init_mlx(t_game *game);

void	free_map(char **map);
int	clean_exit(t_game *game);

#endif
