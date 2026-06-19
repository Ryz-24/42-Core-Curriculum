#include "libft.h"

int	ft_tolower(int a)
{
	if (a >= 'A' && a <= 'Z')
		a += 32;
	return (a);
}
/*int main()
{
	printf("ft_tolower('G') = '%c'\n",ft_tolower('G'));
}*/