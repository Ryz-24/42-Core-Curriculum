/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:15:23 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/17 14:18:15 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = 0;
	if (!s || !f)
		return (NULL);
	while (s[len] != '\0')
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char letter(unsigned int i, char c)
{
    if(c == 'a')
        return (c);
    return ('b');
}
int main(void)
{
    char *result = ft_strmapi("abcda", letter);
    if (result)
    {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}*/
