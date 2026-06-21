#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*int main(void)
{
    printf("ft_isprint('A') = %d\n", ft_isprint('A'));
    printf("ft_isprint('!') = %d\n", ft_isprint('!'));
    printf("ft_isprint('\\n') = %d\n", ft_isprint('\n'));
}*/