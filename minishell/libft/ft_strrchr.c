#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strrchr("hello", 'e'));

	char *a = "Hello";
	char *p = ft_strrchr(a, 'e');
	if (p)
		printf("true\n");
	else
		printf("false\n");
}*/