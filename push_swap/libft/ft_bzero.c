/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:29:12 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/12 18:38:09 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(((unsigned char *)s)[i]) = 0;
		i++;
	}
}
/*
int main()
{
	char ar[2] = {1, 2};
	ft_bzero(ar, 2);
	if(ar[0] == 0 && ar[1] == 0)
		printf("pass");
	else
		printf("fail");
}*/
