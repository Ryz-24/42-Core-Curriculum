/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:18:57 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/17 14:21:00 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void letter(unsigned int i, char *c)
{
    if(c[i] != 'a')
        c[i] = 'b';
}
int main(void)
{
    char ss[] = "abbca";
    ft_striteri(ss, letter);
    printf("%s\n", ss);
    return 0;
}*/
