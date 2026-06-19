#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		return (ptr);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
/*
#include <stdio.h>
int main()
{
	unsigned int *pt;
	
	pt = ft_calloc(4, 4);
	pt[0] = 1;
	pt[2] = 2;
	int i = 0;
	while (i < 4)
	{
		printf("%d", pt[i]);
		i++;
	}
	free (pt);
}*/
