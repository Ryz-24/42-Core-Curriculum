#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
#include <fcntl.h>
int main()
{
	int fd = open("random.txt", O_WRONLY| O_CREAT| O_TRUNC, 0644);
	if(fd == -1)
		return (1);
	ft_putstr_fd("abcd", fd);
	close(fd);
}*/