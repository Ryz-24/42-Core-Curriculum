#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int main (void)
{
	printf("ft_isdigit('z') = %d\n", ft_isdigit('z'));
	printf("ft_isdigit('5') = %d\n", ft_isdigit('5'));
}*/