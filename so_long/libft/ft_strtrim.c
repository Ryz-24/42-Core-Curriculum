/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:36:29 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/17 14:14:53 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	total;
	char	*newstr;

	i = 0;
	start = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > 0 && ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	total = end - start;
	newstr = (char *)malloc((total + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (i < total)
		newstr[i++] = s1[start++];
	newstr[i] = '\0';
	return (newstr);
}
/*
int main(void)
{
    printf("Substring: %s\n", ft_strtrim("xxx42xx", "x"));
    printf("Substring: %s\n", ft_strtrim("", "x"));
    printf("Substring: %s\n", ft_strtrim("xxx", "x"));
    printf("Substring: %s\n", ft_strtrim(NULL, "x"));
    printf("Substring: %s\n", ft_strtrim("   ", " "));
}*/
