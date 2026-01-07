#include "so_long.h"

void	error_msg(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(1);
}


int	main(int argc, char **argv)
{
	if(argc != 2)
		error_msg("Invalid arguments\n");
	return (0);
}
