/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:21:34 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/20 16:08:01 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		i;
	size_t		len;
	char		*ptr;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int main(void)
{
    char *s = "Hello!";
    char *copy = ft_strdup(s);
    if (copy)
    {
        printf("Original: %s\n", s);
        printf("Duplicate: %s\n", copy);
        free(copy);
    }
    free(copy);
    return 0;
}*/
