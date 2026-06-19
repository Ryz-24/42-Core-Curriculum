#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*int main(void)
{
    printf("ft_isalnum('A') = %d\n", ft_isalnum('A'));
    printf("ft_isalnum('5') = %d\n", ft_isalnum('5'));
}*/