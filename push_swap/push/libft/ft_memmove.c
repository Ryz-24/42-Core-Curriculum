/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:51:23 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/31 13:12:07 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src || n == 0)
		return (dest);
	if (dest <= src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1]
				= ((const unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
//#include <stdio.h>
/*
int main()
{
    char sr[] = "123456789";
    ft_memmove(sr + 3, sr, 5);
    printf("after: %s\n", sr);
}*/
