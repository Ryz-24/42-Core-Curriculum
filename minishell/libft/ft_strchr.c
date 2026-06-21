#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strchr("hello", '\0'));

	char *a = "Hello";
	char *p = ft_strchr(a, 'e');
	if (p)
		printf("true\n");
	else
		printf("false\n");
}*/