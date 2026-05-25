/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzaatreh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:18:49 by rzaatreh          #+#    #+#             */
/*   Updated: 2025/08/12 13:25:49 by rzaatreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int main (void)
{
	printf("ft_isdigit('z') = %d\n", ft_isdigit('z'));
	printf("ft_isdigit('5') = %d\n", ft_isdigit('5'));
}*/
