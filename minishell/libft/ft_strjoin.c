/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:56:14 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/17 16:54:29 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*newstr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (i < s1_len)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (i < (s1_len + s2_len))
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}
/*
int main(void)
{
	char *res = ft_strjoin("hello ","world");
    	if(res)
	{
		printf("Subjoin: %s\n", res);
    		free(res);
	}
	return (0);
}*/
